//http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#include <iostream>
#include "Algorithm.h"
#include <cmath>

Population Algorithm::EvolvePopulation(Population & pop) {
	Population newPopulation(pop.GetPopulationSize(), false);

	if (elitism) {
		newPopulation.SaveIndividual(0, pop.GetFittest());
	}

	// crossover
	int elitismOffset;
	if (elitism) {
		elitismOffset = 1;
	}
	else {
		elitismOffset = 0;
	}

	int numPop = pop.GetPopulationSize();
	for (int i = elitismOffset; i < numPop; i++) {
		Individual indiv1 = TournamentSelection(pop);
		Individual indiv2 = TournamentSelection(pop);
		Individual newIndiv = Crossover(indiv1, indiv2);
		newPopulation.SaveIndividual(i, newIndiv);
	}

	// mutate
	int newPopSize = newPopulation.GetPopulationSize();
	for (int i = elitismOffset; i < newPopSize; i++) {
		Mutate(newPopulation.GetIndividual(i));
	}

	return newPopulation;
}

Individual Algorithm::Crossover(Individual & indiv1,
	Individual & indiv2) {
	Individual newSol;
	// Loop through genes
	int indiv1Size = indiv1.Size();
	for (int i = 0; i < indiv1Size; i++) {
		// Crossover
		if (Algorithm::RandomValue() <= uniformRate) {
			newSol.SetGene(i, indiv1.GetGene(i));
		}
		else {
			newSol.SetGene(i, indiv2.GetGene(i));
		}
	}
	return newSol;
}

float Algorithm::RandomValue() {
	// std::random causes memory errors with
	// dr memory, use C++ rand
	//static std::random_device rd;
	// Standard mersenne_twister_engine seeded with rd()
	//static std::mt19937 gen(rd());
	//static std::uniform_real_distribution<>dis(0.0f, 1.0f);

	//return dis(gen);
	return (float)rand() / (float)RAND_MAX;
}

void Algorithm::Mutate(Individual & indiv) {
	Individual newSol;
	int numGenes = indiv.Size();

	for (int i = 0; i < numGenes; i++) {
		if (Algorithm::RandomValue() <= mutationRate) {
			int gene = (int)round(Algorithm::RandomValue());
			indiv.SetGene(i, gene);
		}
	}
}

/// <summary>
/// Get fittest from a random selection of individuals. 
/// </summary>
Individual Algorithm::TournamentSelection(Population& pop) {
	Population tournament(tournamentSize, false);
	int popSize = pop.GetPopulationSize();
	for (int i = 0; i < tournamentSize; i++) {
		int randomId = (int)(Algorithm::RandomValue() * popSize);
		tournament.SaveIndividual(i, pop.GetIndividual(randomId));
	}
	Individual fittest = tournament.GetFittest();
	return fittest;
}