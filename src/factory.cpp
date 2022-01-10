//
// Created by peter on 19.12.2021.
//
//Członkowie grupy:
//(1) Piotr Wolnik, 403077
//(2) Kamil Kosakowski, 405035
//(3) Mikołaj Kapera, 405208
//
//Kierownik grupy: Piotr Wolnik
//
//URL repozytorium: https://github.com/PiotrWolnik/NetSim.git

#include "factory.hpp"
#include "nodes.hpp"
#include <stdexcept>


bool Factory::is_consistent() {
    using colors_map = std::map<const PackageSender*, NodeColor>;
    auto color = colors_map();
    for (auto & node : ramp_collection) {
        color.emplace(&node, NodeColor::UNVISITED);
    }
    for (auto & node : worker_collection) {
        color.emplace(&node, NodeColor::UNVISITED);
    }

    try {
        for (auto & color_ : color) {
            if (!has_reachable_storehouse(color_.first, color))
                throw std::logic_error("Sender has no connection.");
        }
    }
    catch(const std::logic_error& log_error) {
        return false;
    }
    return true;
}

bool
Factory::has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors) {
    if (node_colors[sender] == NodeColor::VERIFIED) {
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;

    if (sender->receiver_preferences_.get_preferences().empty()) {
        throw std::logic_error("No defined receivers.");
    }

    if (std::find_if(sender->receiver_preferences_.begin(), sender->receiver_preferences_.end(),
                     [&sender](auto & elem){ return dynamic_cast<PackageSender*>(elem.first) != sender; }) == sender->receiver_preferences_.end()) {

        for (auto& receiver : sender->receiver_preferences_.get_preferences()) {

            if (receiver.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
                if (std::find_if(sender->receiver_preferences_.begin(), sender->receiver_preferences_.end(),
                                 [&sender](auto& elem) {
                                     return dynamic_cast<PackageSender*>(elem.first) != sender;
                                 }) != sender->receiver_preferences_.end())
                    return true;

            }

            else if (receiver.first->get_receiver_type() == ReceiverType::WORKER) {
                IPackageReceiver* receiver_ptr = receiver.first;
                auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
                auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);

                if (sendrecv_ptr == sender)
                    continue;
                if (std::find_if(sender->receiver_preferences_.begin(), sender->receiver_preferences_.end(),
                                 [&sender](auto& elem) {
                                     return dynamic_cast<PackageSender*>(elem.first) != sender;
                                 }) != sender->receiver_preferences_.end()) {
                    return true;
                }

                if (node_colors[sendrecv_ptr] == NodeColor::UNVISITED)
                    has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;

    if (std::find_if(sender->receiver_preferences_.begin(), sender->receiver_preferences_.end(),
                     [&sender](auto & elem){ return dynamic_cast<PackageSender*>(elem.first) != sender; }) != sender->receiver_preferences_.end())
        return true;
    else
        throw std::logic_error("No defined receivers");
}

void Factory::do_deliveries(Time t) {
    for (auto & ramp : ramp_collection) {
        ramp.deliver_goods(t);
    }
}

void Factory::do_package_passing() {
    for (auto & ramp : ramp_collection) {
        ramp.send_package();
    }
    for (auto & worker : worker_collection) {
        worker.send_package();
    }
}

void Factory::do_work(Time t) {
    for (auto & worker : worker_collection)
        worker.do_work(t);
}

//Członkowie grupy:
//(1) Piotr Wolnik, 403077
//(2) Kamil Kosakowski, 405035
//(3) Mikołaj Kapera, 405208
//
//Kierownik grupy: Piotr Wolnik
//
//URL repozytorium: https://github.com/PiotrWolnik/NetSim.git
