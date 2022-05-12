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
#ifndef SIECI_REPORTS_HPP
#define SIECI_REPORTS_HPP

#include "factory.hpp"

void generate_structure_report(const Factory & f, std::ostream & os);
void generate_simulation_turn_report(const Factory & f, std::ostream & os, Time t);

class IntervalReportNotifier {
public:
    explicit IntervalReportNotifier(TimeOffset t) : delta_t_(t) {}
    bool should_generate_report(Time t);
private:
    TimeOffset delta_t_;
};

class SpecificTurnsReportNotifier {
public:
    explicit SpecificTurnsReportNotifier(std::set<Time> turns) : turns_(std::move(turns)) {}
    bool should_generate_report(Time t);
private:
    std::set<Time> turns_;
};

#endif //SIECI_REPORTS_HPP
//Członkowie grupy:
//(1) Piotr Wolnik, 403077
//(2) Kamil Kosakowski, 405035
//(3) Mikołaj Kapera, 405208
//
//Kierownik grupy: Piotr Wolnik
//
//URL repozytorium: https://github.com/PiotrWolnik/NetSim.git