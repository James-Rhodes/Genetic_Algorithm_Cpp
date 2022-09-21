#include <iostream>
#include "GeneticAlgorithm.hpp"
#include "Parabola.hpp"


int main()
{
    std::cout << "----- Optimising the max value of a Parabola with Pruning -----" << std::endl;
    auto test = GA_Cpp::GeneticAlgorithm<Parabola>(100,0.3f,3);

    test.SetSelectionFunction(GA_Cpp::TournamentSelection<Parabola,0.4f>);
    test.SetPruneFrequency(101); // Prune the population on the 101th run of Optimise
    std::cout << "\n----- Beginning Optimisation -----" << std::endl;
    for (int i = 0; i < 100; i++) {
        test.Optimise();   
    }

    std::cout << "\n----- Optimisation Complete -----\n" << std::endl;


    std::cout << "Final Generation achieved after "<<test.GetNumberOfIterations()<<" iterations: " << std::endl;
    test.LogPreviousGeneration();

    test.Optimise();

    std::cout << "\n\nAfter pruning the population:" << std::endl;
    test.LogPreviousGeneration();
    

}