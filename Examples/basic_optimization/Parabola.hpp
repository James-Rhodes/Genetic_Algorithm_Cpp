#pragma once
#include <iostream>
#include "PopulationMember.hpp"

class Parabola : public GA_Cpp::PopulationMember<Parabola> {
public:
    Parabola() {

    };

    void LogParameters() const override {
        std::cout << fitness << std::endl;
    };

    void Init() override {
    };

    void CrossOver(const Parabola& parentA, const Parabola& parentB) override {};

    void Mutate(float mutationRate) override {};

    double CalculateFitness() override {
        return 0.0;
    };

};
