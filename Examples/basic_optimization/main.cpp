#include <iostream>
#include "GeneticAlgorithm.hpp"
#include "Parabola.hpp"


int main()
{
    std::cout << "Hello Example Project" << std::endl;
    auto test = GA_Cpp::GeneticAlgorithm<Parabola>(10,0.2f,1,GA_Cpp::SelectionAlgorithm::tournament);

    test.Optimise();
}