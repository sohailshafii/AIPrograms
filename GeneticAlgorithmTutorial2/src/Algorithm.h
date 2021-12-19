//http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#pragma once

#include "Population.h"
#include "Individual.h"

class Algorithm {
public:
	static Population EvolvePopulation(Population & pop);

private:
	static constexpr double uniformRate = 0.5;
	static constexpr double mutationRate = 0.0015;
	static constexpr int tournamentSize = 5;
	static constexpr bool elitism = true;

	static Individual Crossover(Individual & indiv1,
		Individual & indiv2);
	static void Mutate(Individual & indiv);
	static Individual TournamentSelection(Population & pop);

	static float RandomValue();

};
