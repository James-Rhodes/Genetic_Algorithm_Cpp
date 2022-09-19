#pragma once
#include <random>
#include <chrono>
#include <ctime>

namespace GA_Cpp
{
	template<typename popType>
	class PopulationMember
	{
	public:
		PopulationMember() = default;

		virtual void LogParameters() const {};

		// Initialise the member of the population with random values
		virtual void Init() = 0;

		// Perform crossover. This acts on the current instance taking in parentA and parentB to alter the current instance
		virtual void CrossOver(const popType& parentA, const popType& parentB) = 0;

		// Perform mutation on the current instance. Takes in the mutation rate as it could be useful for determining which parameters of the instance to change
		virtual void Mutate(float mutationRate) = 0;

		// Calculate the fitness of the current instance. This will be maximised by the genetic algorithm
		virtual double CalculateFitness() = 0;

		void SetFitness(double newFitness) {
			fitness = newFitness;
		}

		double GetFitness() const {
			return fitness;
		}

		double fitness = 0;
	};

	double GetRandom01()
	{
		static std::mt19937 e((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
		static std::uniform_real_distribution<> dis(0, 1); // range 0 - 1
		return dis(e);
	}
}