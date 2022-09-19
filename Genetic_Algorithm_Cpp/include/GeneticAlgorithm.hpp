#pragma once

#include "PopulationMember.hpp"
#include <vector>
#include <iostream>
#include <type_traits>

namespace GA_Cpp
{

	template <typename popType>
	class GeneticAlgorithm
	{
	public:
		GeneticAlgorithm(int populationSize):m_populationSize(populationSize) {

			static_assert(std::is_base_of<PopulationMember<popType>, popType>::value, "\nERROR: The Population Member you have passed in does not derive from base class PopulationMember...\nERROR: Please inherit from this base type. This is achieved using CRTP.\nERROR: eg. class YourClass : public PopulationMember<YourClass>{}\n");

			InitAll();

		};



	private:
		int m_populationSize;

		std::vector<popType> m_population;

		void InitAll() {
			for (popType& popMember : m_population) {
				popMember.Init();
			}
		}
	};
}