//
// Created by peter on 19.12.2021.
//

#ifndef SIECI_FACTORY_HPP
#define SIECI_FACTORY_HPP

#include <vector>
#include "types.hpp"
#include "nodes.hpp"

template <class Node>
class NodeCollection {
public:
    using container_t = typename std::vector<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    void add(Node && node);
    void remove_by_id(ElementID id);
    iterator find_by_id(ElementID id) {
        return std::find_if(collection_.begin(), collection_.end(),
                            [&id](const auto & element){ return id == element.get_id();});
    }
//    const_iterator find_by_id(ElementID id) {
//        return std::find_if(collection_.cbegin(), collection_.cend(),
//                            [&id](const auto & element){ return id == element.get_id();});
//    }
    const_iterator begin() const { return collection_.begin(); }
    const_iterator cbegin() const { return collection_.cbegin(); }
    const_iterator end() const { return collection_.end(); }
    const_iterator cend() const { return collection_.cend(); }
    iterator begin() { return collection_.begin(); }
    iterator end() { return collection_.end(); }
private:
    container_t collection_;
};


class Factory {
public:
    enum class NodeColor { UNVISITED, VISITED, VERIFIED };
    // Dla obiektów klasy Ramp
    void add_ramp(Ramp && ramp);
    void remove_ramp(ElementID id);
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator ramp_cbegin();
    NodeCollection<Ramp>::const_iterator ramp_cend();
    // Dla obiektów klasy Worker
    void add_worker(Worker && worker);
    void remove_worker(ElementID id);
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id);
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id);
    NodeCollection<Worker>::const_iterator worker_cbegin();
    NodeCollection<Worker>::const_iterator worker_cend();
    // Dla obiektów klasy Storehouse
    void add_storehouse(Storehouse && storehouse);
    void remove_storehouse(ElementID id);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id);
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id);
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin();
    NodeCollection<Storehouse>::const_iterator storehouse_cend();
    // Metody realizujące "logikę biznesową"
    bool is_consisten(void);
    void do_deliveries(Time t);
    void do_package_passing(void);
    void do_work(Time t);
    bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);

private:
    //NodeCollection<IPackageReceiver> collection;
    void remove_receiver(NodeCollection<NodeCollection::Node>& collection, ElementID id);
};


template<class Node>
void NodeCollection<Node>::add(Node&& node) {
    if (find_by_id(node.get_id()) == collection_.end()) {
        collection_.push_back(std::move(node));
    }
}

template<class Node>
void NodeCollection<Node>::remove_by_id(ElementID id) {
    if (find_by_id(id) != collection_.end()) {
        collection_.erase(find_by_id(id));
    }
}



#endif //SIECI_FACTORY_HPP
