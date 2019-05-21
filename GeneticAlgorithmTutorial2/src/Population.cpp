#include "Population.h"

Population::Population(int populationSize, bool
	initialize) {
	this->populationSize = populationSize;
	individuals = new Individual[populationSize];
	if (initialize) {
		// Loop and create individuals
        for (int i = 0; i < populationSize; i++) {
            Individual newIndividual;
            newIndividual.generateIndividual();
            saveIndividual(i, newIndividual);
        }
	}
}

Population::~Population() {
	if (individuals != nullptr) {
		delete [] individuals;
	}
}
