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
#ifndef SIECI_PACKAGE_HPP
#define SIECI_PACKAGE_HPP

#include "types.hpp"
#include <utility>


class Package {
public:
    explicit Package() noexcept;
    Package(ElementID ID);
    Package(Package && package) noexcept;
    Package & operator=(Package && package) noexcept;
    ElementID get_id() const { return ID_; }
    ~Package();
private:
    ElementID ID_;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};

#endif //SIECI_PACKAGE_HPP

//Członkowie grupy:
//(1) Piotr Wolnik, 403077
//(2) Kamil Kosakowski, 405035
//(3) Mikołaj Kapera, 405208
//
//Kierownik grupy: Piotr Wolnik
//
//URL repozytorium: https://github.com/PiotrWolnik/NetSim.git