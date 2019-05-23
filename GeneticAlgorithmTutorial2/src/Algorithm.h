//http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#pragma once

#include "Population.h"
#include "Individual.h"

class Algorithm {
public:

	static Population evolvePopulation(Population& pop);
	static Individual crossover(Individual &indiv1,
		Individual &indiv2);
	static void mutate(Individual &indiv);
	static Individual tournamentSelection(Population& pop);

	static float randomValue();

private:

	static constexpr double uniformRate = 0.5;
	static constexpr double mutationRate = 0.0015;
	static constexpr int tournamentSize = 5;
	static constexpr bool elitism = true;

};
