#pragma once
#include <iostream>
#include "PopulationMember.hpp"

// Basic idea is to optimise a parabola. ie. find the x value that corresponds to the 
// maximum value of a known curve y = -100*x^2 + 100
// The corresponding x value should be 0
class Parabola : public GA_Cpp::PopulationMember<Parabola> {
public:
    Parabola() = default;

    void LogParameters() const override {
        std::cout << fitness << std::endl;
    };

    void Init() override {
    };

    void CrossOver(const Parabola& parentA, const Parabola& parentB) override {};

    void Mutate(float mutationRate) override {};

    double CalculateFitness() override {
        return (-100 * xVal * xVal + 100);
    };

private:
    float xVal = 123; // Not needed. This simply gets rid of the compiler error complaining that this variable is not initialised
};
