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

Population::Population(const Population &p2) {
	allocateAndCopyFrom(p2);
}

Population& Population::operator=(
	const Population& other) {
	if (this != &other) {
		if (this->populationSize != other.populationSize) {
			if (this->individuals != nullptr) {
				delete [] individuals;
			}
			allocateAndCopyFrom(other);
		}
		else {
			copyFrom(other);
		}
	}
	return *this;
}

void Population::allocateAndCopyFrom(const Population &other) {
	this->populationSize = other.populationSize;
	this->individuals = new Individual[populationSize];
	copyFrom(other);
}

void Population::copyFrom(const Population &other) {
	for (int i = 0; i < populationSize; i++) {
		this->individuals[i] = other.individuals[i];
	}
}

Population::~Population() {
	if (individuals != nullptr) {
		delete [] individuals;
	}
}
