#include "Population.h"

Population::Population(int populationSize,
	bool initialize) {
	this->populationSize = populationSize;
	individuals = new Individual[populationSize];
	if (initialize) {
		// Loop and create individuals
		for (int i = 0; i < populationSize; i++) {
			Individual newIndividual;
			newIndividual.GenerateIndividual();
			SaveIndividual(i, newIndividual);
		}
	}
}

Population::Population(Population  const & p2) {
	AllocateAndCopyFrom(p2);
}

Population& Population::operator=(
	const Population& other) {
	if (this != &other) {
		if (this->populationSize != other.populationSize) {
			if (this->individuals != nullptr) {
				delete[] individuals;
			}
			AllocateAndCopyFrom(other);
		}
		else {
			CopyFrom(other);
		}
	}
	return *this;
}

void Population::AllocateAndCopyFrom(Population  const & other) {
	this->populationSize = other.populationSize;
	this->individuals = new Individual[populationSize];
	CopyFrom(other);
}

void Population::CopyFrom(Population  const & other) {
	for (int i = 0; i < populationSize; i++) {
		this->individuals[i] = other.individuals[i];
	}
}

Population::~Population() {
	if (individuals != nullptr) {
		delete[] individuals;
	}
}
