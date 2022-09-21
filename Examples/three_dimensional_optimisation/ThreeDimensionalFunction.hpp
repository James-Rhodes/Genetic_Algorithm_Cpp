#pragma once
#include <iostream>
#include <cmath>
#include "PopulationMember.hpp"

// Find the x and y value that corresponds to the 
// maximum value of a known curve z = 0.01*(sin(10*x)/x)*(sin(10*y)/y)
// The corresponding x and y values should be 0 and 0 respectively
class ThreeDimensionalFunction : public GA_Cpp::PopulationMember<ThreeDimensionalFunction> {
public:
    ThreeDimensionalFunction() = default;

    void LogParameters() const override {
        std::cout << "Value X: " << m_xVal<<" and Y: "<<m_yVal<< " with Fitness : "<< fitness << std::endl;
    };

    void Init() override {
        m_xVal = 10 * ((float)GA_Cpp::GetRandom01() * 2 - 1); // Generates a random value between -10 and 10
        m_yVal = 10 * ((float)GA_Cpp::GetRandom01() * 2 - 1); // Generates a random value between -10 and 10
    };

    void CrossOver(const ThreeDimensionalFunction& parentA, const ThreeDimensionalFunction& parentB) override {
        float averageValX = (parentA.m_xVal + parentB.m_xVal) / 2;
        float averageValY = (parentA.m_yVal + parentB.m_yVal) / 2;

        m_xVal = averageValX; // Crude crossover for one variable. Make it the average of the parents values
        m_yVal = averageValY; // Crude crossover for one variable. Make it the average of the parents values
    
    };

    void Mutate(float mutationRate) override {
        Init(); // Just randomly reassign the value of x as we did in the Init function
    };

    double CalculateFitness() override {
        return (std::sin(10 * m_xVal) / m_xVal) * (std::sin(10 * m_yVal) / m_yVal);
    };

private:
    float m_xVal = 123; // Not needed. This simply gets rid of the compiler error complaining that this variable is not initialised
    float m_yVal = 123;
};
