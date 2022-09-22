# Genetic Algorithm Cpp

This is a toy Genetic Algorithm header only library written to be highly customizable to suit many use cases. It was written mainly for my own learning as well as for uses within graphical applications where the interface is particularly well suited (simply call Optimise each frame).

## Overview of the Library

This library is simple to use. There are two header files, GeneticAlgorithm.hpp and PopulationMember.hpp. The PopulationMember.hpp file contains an interface/virtual class. This class defines a member of the population within the genetic algorithm as well as the functions necessary for it to operate correctly (CrossOver, Mutate, Init etc.). The interface is designed using the CRTP.

The GeneticAlgorithm.hpp file contains a class that will facilitate the genetic algorithm. It is a template class, requiring the type passed in to be inherited from the interface defined in PopulationMember.hpp. This class offers a few basic interfaces, firstly it allows for the user to call Optimise which will run one generation of the genetic algorithm. It also has a number of parameters that can be tweaked such as mutationRate, number of members of the population, pruning + associated parameters (removing duplicate members of the population) and the ability to define a custom selection method (defines how to select the members of the population for crossover).

## Examples and Documentation

Examples are included in the git repo. To run the examples (assuming you are on windows) simply clone the repo and run the build_solution.bat file. This will generate a visual studio 2022 solution that can run each example.
