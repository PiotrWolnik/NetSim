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
#include "simulation.hpp"

void simulate(Factory & f, TimeOffset d, std::function<void(Factory&, Time)> rf) {
    if(f.is_consistent()) {
        for (Time t = 1; t < d; ++t) {
            f.do_deliveries(t);
            f.do_package_passing();
            f.do_work(t);
            rf(f, t);
        }
    }
    else
        throw std::logic_error("Factory structure inconsistent");
}
//Członkowie grupy:
//(1) Piotr Wolnik, 403077
//(2) Kamil Kosakowski, 405035
//(3) Mikołaj Kapera, 405208
//
//Kierownik grupy: Piotr Wolnik
//
//URL repozytorium: https://github.com/PiotrWolnik/NetSim.git