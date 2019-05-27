//http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#include <iostream>
#include "Algorithm.h"
#include <cmath>

Population Algorithm::evolvePopulation(Population& pop) {
	Population newPopulation(pop.getPopulationSize(), false);

	if (elitism) {
		newPopulation.saveIndividual(0, pop.getFittest());
	}

	// crossover
	int elitismOffset;
	if (elitism) {
		elitismOffset = 1;
	}
	else {
		elitismOffset = 0;
	}

	int numPop = pop.getPopulationSize();
	for (int i = elitismOffset; i < numPop; i++) {
		Individual indiv1 = tournamentSelection(pop);
		Individual indiv2 = tournamentSelection(pop);
		Individual newIndiv = crossover(indiv1, indiv2);
		newPopulation.saveIndividual(i, newIndiv);
	}

	// mutate
	int newPopSize = newPopulation.getPopulationSize();
	for (int i = elitismOffset; i < newPopSize; i++) {
		mutate(newPopulation.getIndividual(i));
	}

	return newPopulation;
}

Individual Algorithm::crossover(Individual &indiv1,
	Individual &indiv2) {
	Individual newSol;
	// Loop through genes
	int indiv1Size = indiv1.size();
	for (int i = 0; i < indiv1Size; i++) {
		// Crossover
		if (Algorithm::randomValue() <= uniformRate) {
			newSol.setGene(i, indiv1.getGene(i));
		}
		else {
			newSol.setGene(i, indiv2.getGene(i));
		}
	}
	return newSol;
}

float Algorithm::randomValue() {
	// std::random causes memory errors with
	// dr memory, use C++ rand
	//static std::random_device rd;
	// Standard mersenne_twister_engine seeded with rd()
	//static std::mt19937 gen(rd());
	//static std::uniform_real_distribution<>dis(0.0f, 1.0f);

	//return dis(gen);
	return (float)rand() / (float)RAND_MAX;
}

void Algorithm::mutate(Individual &indiv) {
	Individual newSol;
	int numGenes = indiv.size();

	for (int i = 0; i < numGenes; i++) {
		if (Algorithm::randomValue() <= mutationRate) {
			int gene = (int)round(Algorithm::randomValue());
			indiv.setGene(i, gene);
		}
	}
}

Individual Algorithm::tournamentSelection(Population& pop) {
	Population tournament(tournamentSize, false);
	int popSize = pop.getPopulationSize();
	for (int i = 0; i < tournamentSize; i++) {
		int randomId = (int)(Algorithm::randomValue() * popSize);
		tournament.saveIndividual(i, pop.getIndividual(randomId));
	}
	Individual fittest = tournament.getFittest();
	return fittest;
}