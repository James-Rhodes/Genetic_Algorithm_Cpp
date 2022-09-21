#include <iostream>
#include "GeneticAlgorithm.hpp"
#include "Parabola.hpp"

// To create your own custom custom selection algorithm follow the following function signature
// int YourSelectionFunc(const std::vector<YourPopulationType>& population)
// The selection func must return the index of the selected member of the population


int RandomSelectionAlgorithm(const std::vector<Parabola> &population)
{
    // Totally useless selection algorithm. 
    return GA_Cpp::GetRandomInt(0, (int)population.size() - 1);
}

int main()
{
    std::cout << "----- Optimizing the max value of a Parabola with Custom Selection Algorithm -----" << std::endl;
    auto test = GA_Cpp::GeneticAlgorithm<Parabola>(100, 0.3f, 3);

    test.SetSelectionFunction(RandomSelectionAlgorithm);

    std::cout << "\n----- Beginning Optimization -----" << std::endl;

    for (int i = 0; i < 100; i++)
    {
        test.Optimise();

        auto best = test.GetBestResult();
        best.LogParameters();
    }
    std::cout << "\n----- Optimization Complete -----\n" << std::endl;

    std::cout << "Final Generation achieved after " << test.GetNumberOfIterations() << " iterations: " << std::endl;
    test.LogPreviousGeneration();

    std::cout << "\n\nBest Performing Population Member: " << std::endl;
    test.LogBestResult();
}