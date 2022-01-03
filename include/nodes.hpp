//
// Created by peter on 19.12.2021.
//

#ifndef SIECI_NODES_HPP
#define SIECI_NODES_HPP

#include <map>
#include <optional>
#include <memory>
#include "types.hpp"
#include "storage_types.hpp"
#include "package.hpp"
#include "helpers.hpp"


enum class ReceiverType {
    WORKER, STOREHOUSE
};


class IPackageReceiver {
public:
    virtual void receive_package(Package && p) = 0;
    virtual ElementID get_id(void) = 0;
    virtual ReceiverType get_receiver_type(void) = 0;
    virtual ~IPackageReceiver() = default;
    virtual IPackageStockpile::const_iterator cbegin() const = 0;
    virtual IPackageStockpile::const_iterator cend() const = 0;
    virtual IPackageStockpile::const_iterator begin() const = 0;
    virtual IPackageStockpile::const_iterator end() const = 0;
};


class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d =
            std::unique_ptr<IPackageStockpile>(new PackageQueue(PackageQueueType::FIFO)))
            : storehouse_(std::move(d)), ID_(id) {}
    // Klasa Worker realizuje interfejs IPackageReceiver dlatego należy przeciążyć metody tej klasy
    void receive_package(Package && p) override;
    ElementID get_id(void) override { return ID_; }
    ReceiverType get_receiver_type(void) override { return ReceiverType::STOREHOUSE; }
    IPackageStockpile::const_iterator cbegin() const override { return storehouse_->cbegin(); }
    IPackageStockpile::const_iterator cend() const override { return storehouse_->cend(); }
    IPackageStockpile::const_iterator begin() const override { return storehouse_->begin(); }
    IPackageStockpile::const_iterator end() const override { return storehouse_->end(); }
private:
    std::unique_ptr<IPackageStockpile> storehouse_;
    ElementID ID_;
};


class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    ReceiverPreferences(ProbabilityGenerator pg = probability_generator);
    void add_receiver(IPackageReceiver* ptr);
    void remove_receiver(IPackageReceiver * ptr);
    IPackageReceiver * choose_receiver(void);
    preferences_t & get_preferences(void);
    const_iterator begin() const;
    const_iterator cbegin() const;
    const_iterator end() const;
    const_iterator cend() const;
    preferences_t preferences;
};


class PackageSender {
public:
    PackageSender() = default;
    PackageSender(PackageSender && package_sender) = default;
    virtual ~PackageSender() = default;
    void send_package(void);
    std::optional<Package> & get_sending_buffer(void) { return buffer_; }
    ReceiverPreferences receiver_preferences_;
//protected:
//    void push_package(Package&& package) { buffer_.emplace(std::move(package)); }
private:
    std::optional<Package> buffer_;
};


class Ramp : public PackageSender {
public:
    Ramp(ElementID id, TimeOffset di) : ID_(id), di_(di) {}
    void deliver_goods(Time t) { t_ =  t + di_; }
    TimeOffset get_delivery_interval(void) { return di_; }
    ElementID get_id(void) { return ID_; }
private:
    ElementID ID_;
    TimeOffset di_;
    Time t_;
};


class Worker : public PackageSender, IPackageReceiver {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> ptr) : ID_(id), pd_(pd), worker_ptr(std::move(ptr)) {}
    void do_work(Time t) { t_ = t + pd_; }
    TimeOffset get_processing_duration(void) { return pd_; }
    Time get_package_processing_start_time(void) { return t_; }
    // Klasa Worker realizuje interfejs IPackageReceiver dlatego należy przeciążyć metody tej klasy
    void receive_package(Package && p) override;
    ElementID get_id(void) override { return ID_; }
    ReceiverType get_receiver_type(void) override { return ReceiverType::WORKER; }
    IPackageStockpile::const_iterator cbegin() const override { return worker_ptr->cbegin(); }
    IPackageStockpile::const_iterator cend() const override { return worker_ptr->cend(); }
    IPackageStockpile::const_iterator begin() const override { return worker_ptr->begin(); }
    IPackageStockpile::const_iterator end() const override { return worker_ptr->end(); }
private:
    ElementID ID_;
    TimeOffset pd_;
    Time t_;
    std::unique_ptr<IPackageQueue> worker_ptr;
};


#endif //SIECI_NODES_HPP
