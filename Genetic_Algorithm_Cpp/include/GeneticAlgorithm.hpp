#pragma once

#include "PopulationMember.hpp"
#include <vector>
#include <iostream>
#include <type_traits>
#include <algorithm>

namespace GA_Cpp
{
	// simple selection is defined in this link as a generic selection algorithm https://en.wikipedia.org/wiki/Selection_(genetic_algorithm)
	enum class SelectionAlgorithm { simple, tournament};

	template <typename popType>
	class GeneticAlgorithm
	{
	public:
		GeneticAlgorithm(int populationSize,float mutationRate, int numElite = 1, SelectionAlgorithm selectionAlgorithm = SelectionAlgorithm::simple)
						:m_populationSize(populationSize),
						 m_population(std::vector<popType>(populationSize)),
						 m_mutationRate(mutationRate),
						 m_numElite(numElite) 
		{

			static_assert(std::is_base_of<PopulationMember<popType>, popType>::value, "\nERROR: The Population Member you have passed in does not derive from base class PopulationMember...\nERROR: Please inherit from this base type. This is achieved using CRTP.\nERROR: eg. class YourClass : public PopulationMember<YourClass>{}\n");

			switch (selectionAlgorithm) {

			case(SelectionAlgorithm::simple):
				selectionFunc = &GeneticAlgorithm::SimpleSelection;
				break;
			case(SelectionAlgorithm::tournament):
				selectionFunc = &GeneticAlgorithm::TournamentSelection;
				break;
			};

			//(this->*selectionFunc)(); How to call the function pointer ... 

			InitAll();

			CrossOverAll();
		};

		void SetSelectionPoolPercentage(float selectionPoolPercentage) {
			m_selectionPoolPercentage = selectionPoolPercentage;
		}

	private:
		int m_populationSize;
		std::vector<popType> m_population;
		float m_mutationRate;
		int m_numElite;
		double m_totalFitness = 0;
		float m_selectionPoolPercentage = 0.3f; // How much of the selection pool to be used for tournament selection

		int (GeneticAlgorithm::*selectionFunc)() const;

		void InitAll() {
			for (popType& popMember : m_population) {
				popMember.Init();
			}
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
					int parentAIndex = (this->*selectionFunc)();
					int parentBIndex = (this->*selectionFunc)();

					while (parentAIndex == parentBIndex) {
						parentBIndex = (this->*selectionFunc)();
					}

					populationMember.CrossOver(m_population[parentAIndex], m_population[parentBIndex]);
				}
				i++;
			}
			std::swap(m_population, newGeneration);

		};

		void MutateAll() {

			for (popType& populationMember : m_population) {
				float randomNum = GetRandom01();
				if (randomNum < m_mutationRate) {
					populationMember.Mutate();
				}
			}
		};

		void CalculateAllFitness() {
			m_totalFitness = 0;

			for (popType& populationMember : m_population) {
				double fitness = populationMember.CalculateFitness();
				populationMember.SetFitness(fitness);

				m_totalFitness += fitness;
			}
		};

		int SimpleSelection() const {
			std::cout << "Simple Selection" << std::endl;
			return 0;
		};

		int TournamentSelection() const {
			// Performs selection using the tournament selection method. This can be found here: https://en.wikipedia.org/wiki/Tournament_selection
			int bestIndex = -1;
			int selectionPool = (int)(m_populationSize * m_selectionPoolPercentage);
			for (int i = 0; i < selectionPool; i++)
			{
				int randIndex = GetRandomInt(0, m_populationSize - 1);
				if (bestIndex == -1)
				{
					bestIndex = randIndex;
				}
				else if (m_population[randIndex].fitness > m_population[bestIndex].fitness)
				{
					bestIndex = randIndex;
				}
			}

			return bestIndex;
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