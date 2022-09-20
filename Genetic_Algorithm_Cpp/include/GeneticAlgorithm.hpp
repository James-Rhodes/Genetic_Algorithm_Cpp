#pragma once

#include "PopulationMember.hpp"
#include <vector>
#include <iostream>
#include <type_traits>

namespace GA_Cpp
{
	// simple selection is defined in this link as a generic selection algorithm https://en.wikipedia.org/wiki/Selection_(genetic_algorithm)
	enum class SelectionAlgorithm { simple, tournament};

	template <typename popType>
	class GeneticAlgorithm
	{
	public:
		GeneticAlgorithm(int populationSize,float mutationRate, SelectionAlgorithm selectionAlgorithm = SelectionAlgorithm::simple)
						:m_populationSize(populationSize),
						 m_population(std::vector<popType>(populationSize)),
						 m_mutationRate(mutationRate) {

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

		};



	private:
		int m_populationSize;
		std::vector<popType> m_population;
		float m_mutationRate;

		int (GeneticAlgorithm::*selectionFunc)() const;

		void InitAll() {
			for (popType& popMember : m_population) {
				popMember.Init();
			}
		}

		void CrossOverAll() {

		};

		void MutateAll() {

		};

		void CalculateAllFitness() {
		};

		int SimpleSelection() const {
			std::cout << "Simple Selection" << std::endl;
			return 0;
		};

		int TournamentSelection() const {
			std::cout << "Tournament Selection" << std::endl;
			return 0;
		};
	};
}