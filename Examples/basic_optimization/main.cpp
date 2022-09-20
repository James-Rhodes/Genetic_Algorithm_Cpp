#include <iostream>
#include "GeneticAlgorithm.hpp"
#include "Parabola.hpp"


int main()
{
    std::cout << "Hello Example Project" << std::endl;
    auto test = GA_Cpp::GeneticAlgorithm<Parabola>(100,0.2f,GA_Cpp::SelectionAlgorithm::tournament);
}