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
        xVal = 100 * (GA_Cpp::GetRandom01() * 2 - 1); // Generates a random value between -100 and 100
    };

    void CrossOver(const Parabola& parentA, const Parabola& parentB) override {
        float averageVal = (parentA.xVal + parentB.xVal) / 2;
        xVal = averageVal; // Crude crossover for one variable. Make it the average of the parents values
    };

    void Mutate(float mutationRate) override {
        Init(); // Just randomly reassign the value of x as we did in the Init function
    };

    double CalculateFitness() override {
        return (-100 * xVal * xVal + 100);
    };

private:
    float xVal = 123; // Not needed. This simply gets rid of the compiler error complaining that this variable is not initialised
};
