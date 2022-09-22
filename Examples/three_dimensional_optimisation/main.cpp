#include <iostream>
#include "GeneticAlgorithm.hpp"
#include "ThreeDimensionalFunction.hpp"


int main()
{
    std::cout << "----- Optimizing the max value of a Parabola -----" << std::endl;
    auto test = GA_Cpp::GeneticAlgorithm<ThreeDimensionalFunction>(100,0.1f,20);

    // Note the selection function is not set. This will cause the GA to use a simple fitness proportional selection method
    // instead. This simple selection method is effective however requires that the fitness always be positive for each
    // member of the population

    test.SetPruneFrequency(100,2); // Prune the population every 100 generations only allowing a maximum of 2 duplicate members of the population
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