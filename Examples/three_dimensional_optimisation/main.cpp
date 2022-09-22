#include <iostream>
#include "GeneticAlgorithm.hpp"
#include "ThreeDimensionalFunction.hpp"


int main()
{
    std::cout << "----- Optimizing the max value of a Parabola -----" << std::endl;
    auto test = GA_Cpp::GeneticAlgorithm<ThreeDimensionalFunction>(100,0.1f,20);

    test.SetSelectionFunction(GA_Cpp::TournamentSelection<ThreeDimensionalFunction,1.0f>);
    test.SetPruneFrequency(100,10);
    std::cout << "\n----- Beginning Optimization -----" << std::endl;
    for (int i = 0; i < 1000; i++) {
        test.Optimise();
        
        auto best = test.GetBestResult();
        best.LogParameters();
    }

    std::cout << "\n----- Optimization Complete -----\n" << std::endl;


    std::cout << "Final Generation achieved after "<<test.GetNumberOfIterations()<<" iterations: " << std::endl;
    test.LogPreviousGeneration();

    std::cout << "\n\nBest Performing Population Member: " << std::endl;
    test.LogBestResult();
}