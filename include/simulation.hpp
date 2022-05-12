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
#ifndef SIECI_SIMULATION_HPP
#define SIECI_SIMULATION_HPP
#include "factory.hpp"

extern void simulate(Factory & f, TimeOffset d, std::function<void(Factory&, Time)> rf);

#endif //SIECI_SIMULATION_HPP
//Członkowie grupy:
//(1) Piotr Wolnik, 403077
//(2) Kamil Kosakowski, 405035
//(3) Mikołaj Kapera, 405208
//
//Kierownik grupy: Piotr Wolnik
//
//URL repozytorium: https://github.com/PiotrWolnik/NetSim.git