#include <iostream>
#include "GeneticAlgorithm.hpp"
#include "Parabola.hpp"


int main()
{
    std::cout << "----- Optimizing the max value of a Parabola -----" << std::endl;
    auto test = GA_Cpp::GeneticAlgorithm<Parabola>(100,0.3f,3);

    test.SetSelectionFunction(GA_Cpp::TournamentSelection<Parabola,0.4f>);

    for (int i = 0; i < 100; i++) {
        test.Optimise();
        
        auto best = test.GetBestResult();
        best.LogParameters();
    }

    std::cout << "Final Generation: " << std::endl;
    test.LogPreviousGeneration();

    std::cout << "Best Performing Population Member: " << std::endl;
    test.LogBestResult();
}