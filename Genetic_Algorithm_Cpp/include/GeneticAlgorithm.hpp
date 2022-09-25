#pragma once

#include "PopulationMember.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <type_traits>
#include <algorithm>

namespace GA_Cpp
{
	enum class SelectionAlgorithm { simple, tournament};

	// Performs selection using the tournament selection method. This can be found here: https://en.wikipedia.org/wiki/Tournament_selection
	// popType = the type of the population used in the genetic algorithm
	// selectionPoolPercentage = how much of the selection pool to be used for tournament selection
	template<typename popType, float selectionPoolPercentage>
	int TournamentSelection(const std::vector<popType>& population) {

		int bestIndex = -1;
		int populationSize = (int)population.size();
		int selectionPool = (int)(populationSize * selectionPoolPercentage);
		for (int i = 0; i < selectionPool; i++)
		{
			int randIndex = GetRandomInt(0, populationSize - 1);
			if (bestIndex == -1)
			{
				bestIndex = randIndex;
			}
			else if (population[randIndex].fitness > population[bestIndex].fitness)
			{
				bestIndex = randIndex;
			}
		}
		return bestIndex;
	}

	// This is the Genetic Algorithm class which facilitates optimising based on the population type passed in as template parameter
	template <typename popType>
	class GeneticAlgorithm
	{
	public:
		// populationSize = how many members per generation
		// mutationRate = what percentage of the population is mutated (0-1 range)
		// numElite = how many of the best performing members of the population persist to the next generation
		GeneticAlgorithm(int populationSize, float mutationRate, int numElite = 1)
			:m_populationSize(populationSize),
			m_population(std::vector<popType>(populationSize)),
			m_mutationRate(mutationRate),
			m_numElite(numElite)
		{

			static_assert(std::is_base_of<PopulationMember<popType>, popType>::value, "\nERROR: The Population Member you have passed in does not derive from base class PopulationMember...\nERROR: Please inherit from this base type. This is achieved using CRTP.\nERROR: eg. class YourClass : public PopulationMember<YourClass>{}\n");
			if (m_populationSize <= 1) {
				std::string error = "\nERROR: There must be at least 2 members of the population for optimisation to occur.";
				std::cout <<error<< std::endl;
				throw error;
			}
			if (m_mutationRate > 1.0f || m_mutationRate < 0.0) {
				std::string error = "\nERROR: Mutation Rate must be between 0 and 1 as it is the percentage of the population that will be mutated.";
				std::cout << error << std::endl;
				throw error;
			}
			if (m_numElite < 0 || m_numElite > m_populationSize) {
				std::string error = "\nERROR: numElite must be between 0 and the size of the population. This is the number of the top performing population persist to the next generation.";
				std::cout << error << std::endl;
				throw error;
			}

			InitAll();

			CalculateAllFitness();
		};

		// Set the selection function which returns an index of which member of the population to select
		void SetSelectionFunction(int (*func)(const std::vector<popType>&)) {
			m_selectionFunc = func;
		}

		// Runs one generation of the genetic algorithm. Run this time until a desired result is reached
		void Optimise() {
			m_iterations++;

			CrossOverAll();
			MutateAll();
			CalculateAllFitness();

			if ((m_pruneFrequency != -1) && ((m_iterations % m_pruneFrequency) == 0)) {
				PrunePopulation();
				CalculateAllFitness(); // Recalculate the Fitness's after pruning
			}
		}
	
		// Returns a reference to the best member of the population
		popType& GetBestResult() {
			return m_population[m_indexOfBestPopulationMember];
		}

		// Logs the best member of the most recent generation
		void LogBestResult() {
			m_population[m_indexOfBestPopulationMember].LogParameters();
		}

		// Logs the most recent Generation
		void LogPreviousGeneration() {
			std::qsort(m_population.data(), m_population.size(), sizeof(popType), GeneticAlgorithm::ComparePopType);
			m_indexOfBestPopulationMember = 0; // The best member of the population is the first in the list now that it has been sorted
			for (popType& populationMember : m_population) {
				populationMember.LogParameters();
			}
		}

		// Returns the number of times Optimize has been called
		uint32_t GetNumberOfIterations() {
			return m_iterations;
		}

		// pruneFrequency = how often the population should have its duplicates removed
		// maxDuplicate = the maximum number of duplicate population members are allowed in the population
		void SetPruneFrequency(int pruneFrequency, int maxDuplicates = 1) {
			if (pruneFrequency < 1) {
				std::string error = "\nERROR: pruneFrequency must be greater than 1 for it to actually prune the population";
				std::cout << error << std::endl;
				throw error;
			}
			m_pruneFrequency = pruneFrequency;
			m_maxDuplicates = maxDuplicates;
		}

		// Initialises all of the members of the population
		void InitAll() {
			for (popType& popMember : m_population) {
				popMember.Init();
			}

			CalculateAllFitness();
		}

	private:
		int m_populationSize;
		std::vector<popType> m_population;
		float m_mutationRate;
		int m_numElite;
		double m_totalFitness = 0;
		int m_indexOfBestPopulationMember = -1;
		uint32_t m_iterations = 0;
		int m_pruneFrequency = -1;
		int m_maxDuplicates = 1;

		int (*m_selectionFunc)(const std::vector<popType>&) = nullptr;

		// Performs crossover on the entire population
		void CrossOverAll() {
			std::vector<popType> newGeneration(m_populationSize);
			std::qsort(m_population.data(), m_population.size(), sizeof(popType), GeneticAlgorithm::ComparePopType);

			int i = 0;
			for (popType& populationMember : newGeneration) {

				if (i < m_numElite) {
					// Number of elite is how many of the best members of the current population to keep unchanged for the next one
					populationMember = m_population[i];
				}
				else {
					int parentAIndex = 0;
					int parentBIndex = 0;

					if (m_selectionFunc == nullptr) {
						parentAIndex = SimpleSelection();
						parentBIndex = SimpleSelection();

						while (parentAIndex == parentBIndex) {
							parentBIndex = SimpleSelection();
						}
					}
					else {
						parentAIndex = m_selectionFunc(m_population);
						parentBIndex = m_selectionFunc(m_population);

						while (parentAIndex == parentBIndex) {
							parentBIndex = m_selectionFunc(m_population);
						}
					}

					populationMember.CrossOver(m_population[parentAIndex], m_population[parentBIndex]);
				}
				i++;
			}
			std::swap(m_population, newGeneration);

		};

		// Performs mutation on the entire population
		void MutateAll() {

			for (popType& populationMember : m_population) {
				double randomNum = GetRandom01();
				if (randomNum < m_mutationRate) {
					populationMember.Mutate(m_mutationRate);
				}
			}
		};

		// Calculates the fitness of each member of the population
		void CalculateAllFitness() {
			m_totalFitness = 0;

			double bestFitness = -INFINITY;
			m_indexOfBestPopulationMember = -1;

			int i = 0;
			for (popType& populationMember : m_population) {
				double fitness = populationMember.CalculateFitness();
				populationMember.SetFitness(fitness);

				if (fitness > bestFitness)
				{
					bestFitness = fitness;
					m_indexOfBestPopulationMember = i;
				}

				m_totalFitness += fitness;
				i++;
			}
		};

		// Selects a member of the population by fitness proportional selection
		// This algorithm will only work for non-negative fitness value
		// simple selection is defined in this link as a generic selection algorithm https://en.wikipedia.org/wiki/Selection_(genetic_algorithm)
		int SimpleSelection() const {


			double randNum = GetRandom01();
			double accumulation = 0;
			double prob;

			while (randNum == 0)
			{
				randNum = GetRandom01();
			}

			for (int i = 0; i < m_populationSize; i++)
			{
				prob = m_population[i].fitness / m_totalFitness;
				accumulation += prob;
				if (accumulation >= randNum)
				{
					return i;
				}
			}
			return m_populationSize - 1;
		};

		// Prunes all the members of the population that are deemed the same
		void PrunePopulation() {
			std::unordered_map<double, int> map;

			for (popType& populationMember : m_population)
			{
				auto currentInsertion = map.insert({ populationMember.fitness , 1 });
				if (!currentInsertion.second) {
					// If the fitness already exists in the map then add 1 to the frequency
					(*currentInsertion.first).second++;

					if ((*currentInsertion.first).second > m_maxDuplicates) {
						// If there are more than the allowed amount of duplicates for each population member then mutate
						
						//populationMember.Init();
						populationMember.Mutate(m_mutationRate);
					}

				}
			}
		}

		// Compares members of the population for sorting
		static int ComparePopType(const void* _a, const void* _b) {
			popType* a = (popType*)_a;
			popType* b = (popType*)_b;

			if (a->fitness < b->fitness)
				return 1;
			if (a->fitness == b->fitness)
				return 0;
			if (a->fitness > b->fitness)
				return -1;
			return (int)NULL;
		}
	};
};