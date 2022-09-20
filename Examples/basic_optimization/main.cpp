#include <iostream>
#include "GeneticAlgorithm.hpp"
#include "Parabola.hpp"


int main()
{
    std::cout << "Hello Example Project" << std::endl;
    auto test = GA_Cpp::GeneticAlgorithm<Parabola>(100,0.8f,10,GA_Cpp::SelectionAlgorithm::tournament);

    for (int i = 0; i < 100; i++) {
        test.Optimise();

        auto best = test.GetBestResult();

        best.LogParameters();
    }
}