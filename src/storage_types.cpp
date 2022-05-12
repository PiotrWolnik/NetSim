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
#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType package_queue_type) {
    switch(package_queue_type) {
        case PackageQueueType::FIFO :
            packageQueueType = PackageQueueType::FIFO;
            break;

        case PackageQueueType::LIFO :
            packageQueueType = PackageQueueType::LIFO;
            break;
    }

    products_ = std::list<Package>();
}


void PackageQueue::push(Package&& package) {
    products_.push_back(std::move(package));
}


Package PackageQueue::pop() {
    Package package_that_is_erased;

    switch (packageQueueType) {
        case PackageQueueType::FIFO :
            package_that_is_erased = std::move(*products_.begin());
            products_.pop_front();
            break;

        case PackageQueueType::LIFO :
            package_that_is_erased = std::move(*products_.end());
            products_.pop_back();
            break;
    }
    return package_that_is_erased;
}


PackageQueueType PackageQueue::get_queue_type() {
    return packageQueueType;
}


std::size_t PackageQueue::size() {
    std::size_t size_of_container = 0;
    for (const_iterator iter = products_.begin(); iter != products_.end(); iter++) {
        size_of_container++;
    }

    return size_of_container;
}

//Członkowie grupy:
//(1) Piotr Wolnik, 403077
//(2) Kamil Kosakowski, 405035
//(3) Mikołaj Kapera, 405208
//
//Kierownik grupy: Piotr Wolnik
//
//URL repozytorium: https://github.com/PiotrWolnik/NetSim.git