//http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#pragma once

#include "Individual.h"
#include <iostream>

class Population {
public:

	Population(int populationSize, bool
		initialize);

	Population(const Population &p2);
	Population& operator=(
		const Population& other);

	~Population();

	Individual& getIndividual(int index) {
		return individuals[index];
	}

	Individual& getFittest() {
		Individual& fittest = individuals[0];

		for (int i = 0; i < populationSize; i++) {
			auto& current = individuals[i];
			if (fittest.getFitness() <= current.getFitness()) {
				fittest = current;
			}
		}

		return fittest;
	}

	int getPopulationSize() const {
		return populationSize;
	}

	void saveIndividual(int index,
		Individual& indiv) {
		individuals[index] = indiv;
	}

	void PrintPropulation() {
		for (int i = 0; i < populationSize; i++) {
			individuals[i].print();
		}
	}

private:
	void allocateAndCopyFrom(const Population &other);
	void copyFrom(const Population &other);

	Individual* individuals;
	int populationSize;
};
