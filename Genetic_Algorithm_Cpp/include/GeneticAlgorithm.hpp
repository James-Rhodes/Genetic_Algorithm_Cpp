#pragma once

#include "PopulationMember.hpp"
#include <vector>
#include <iostream>

namespace GA_Cpp
{

	// Below Template only allows types passed in if they are inherited from PopulationMember
	template <typename T>
	class GeneticAlgorithm
	{
	public:
		GeneticAlgorithm() {
			bool populationMemberBaseOfT = std::is_base_of<PopulationMember, T>::value;

			if (!populationMemberBaseOfT) {
				//Throw error
			std::cout << "Was not derived my dude" << std::endl;
			}
		};

		// T& Optimize() {
		//
		//	return static_cast<T&>(OptimizeInternal());
		// }

	private:
		// PopulationMember* OptimizeInternal();

		std::vector<PopulationMember *> populationPool;
	};
}