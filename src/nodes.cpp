//
// Created by peter on 19.12.2021.
//

#include "nodes.hpp"

ReceiverPreferences::const_iterator ReceiverPreferences::begin() const {
    return preferences.begin();
}

ReceiverPreferences::const_iterator ReceiverPreferences::cbegin() const {
    return preferences.cbegin();
}

ReceiverPreferences::const_iterator ReceiverPreferences::end() const {
    return preferences.end();
}

ReceiverPreferences::const_iterator ReceiverPreferences::cend() const {
    return preferences.cend();
}

void Worker::receive_package(Package&& p) {
    PackageSender::push_package(std::move(p));
}

void Storehouse::receive_package(Package&& p) {
    storehouse_->push(std::move(p));
}
