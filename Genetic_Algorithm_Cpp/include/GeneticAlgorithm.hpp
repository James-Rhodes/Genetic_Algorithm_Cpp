#pragma once

#include "PopulationMember.hpp"
#include <vector>
#include <iostream>
#include <type_traits>
#include <algorithm>

namespace GA_Cpp
{
	enum class SelectionAlgorithm { simple, tournament};


	template<typename popType, float selectionPoolPercentage>
	int TournamentSelection(const std::vector<popType>& population) {
		// Performs selection using the tournament selection method. This can be found here: https://en.wikipedia.org/wiki/Tournament_selection
		// selectionPoolPercentage is how much of the selection pool to be used for tournament selection
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

	template <typename popType>
	class GeneticAlgorithm
	{
	public:
		GeneticAlgorithm(int populationSize, float mutationRate, int numElite = 1)
			:m_populationSize(populationSize),
			m_population(std::vector<popType>(populationSize)),
			m_mutationRate(mutationRate),
			m_numElite(numElite)
		{

			static_assert(std::is_base_of<PopulationMember<popType>, popType>::value, "\nERROR: The Population Member you have passed in does not derive from base class PopulationMember...\nERROR: Please inherit from this base type. This is achieved using CRTP.\nERROR: eg. class YourClass : public PopulationMember<YourClass>{}\n");

			InitAll();

			CrossOverAll();
		};

		void SetSelectionFunction(int (*func)(const std::vector<popType>&)) {
			// Set a custom selection function which returns an index of the selection
			m_selectionFunc = func;
		}

		void Optimise() {
			CrossOverAll();
			MutateAll();
			CalculateAllFitness();

			m_iterations++;
		}
	
		popType& GetBestResult() {
			return m_population[m_indexOfBestPopulationMember];
		}

		void LogBestResult() {
			m_population[m_indexOfBestPopulationMember].LogParameters();
		}

		void LogPreviousGeneration() {
			std::qsort(m_population.data(), m_population.size(), sizeof(popType), GeneticAlgorithm::ComparePopType);

			for (popType& populationMember : m_population) {
				populationMember.LogParameters();
			}
		}

		uint32_t GetNumberOfIterations() {
			// Returns the number of times Optimize has been called
			return m_iterations;
		}

	private:
		int m_populationSize;
		std::vector<popType> m_population;
		float m_mutationRate;
		int m_numElite;
		double m_totalFitness = 0;
		int m_indexOfBestPopulationMember = -1;
		uint32_t m_iterations = 0;

		int (*m_selectionFunc)(const std::vector<popType>&) = nullptr;


		void InitAll() {
			for (popType& popMember : m_population) {
				popMember.Init();
			}

			CalculateAllFitness();
		}

		void CrossOverAll() {
			// Perform crossover on all the population
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

		void MutateAll() {

			for (popType& populationMember : m_population) {
				double randomNum = GetRandom01();
				if (randomNum < m_mutationRate) {
					populationMember.Mutate(m_mutationRate);
				}
			}
		};

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

		int SimpleSelection() const {
			// This algorithm will only work for non-negative fitness value
			// simple selection is defined in this link as a generic selection algorithm https://en.wikipedia.org/wiki/Selection_(genetic_algorithm)

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