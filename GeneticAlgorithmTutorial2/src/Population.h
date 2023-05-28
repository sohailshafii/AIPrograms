//http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#pragma once

#include "Individual.h"
#include <iostream>

class Population {
public:
	Population(int populationSize,
		bool initialize);

	Population(Population  const & p2);
	Population& operator=(Population const & other);

	~Population();

	Individual& GetIndividual(int index) {
		return individuals[index];
	}
	
	Individual const & GetIndividualConst(int index) const {
		return individuals[index];
	}

	Individual& GetFittest() {
		Individual& fittest = individuals[0];

		for (int i = 0; i < populationSize; i++) {
			auto& current = individuals[i];
			if (fittest.GetFitness() <= current.GetFitness()) {
				fittest = current;
			}
		}

		return fittest;
	}

	int GetPopulationSize() const {
		return populationSize;
	}

	void SaveIndividual(int index,
		Individual const & indiv) {
		individuals[index] = indiv;
	}

	void PrintPropulation() {
		for (int i = 0; i < populationSize; i++) {
			individuals[i].Print();
		}
	}

private:
	void AllocateAndCopyFrom(Population  const & other);
	void CopyFrom(Population  const & other);

	Individual* individuals;
	int populationSize;
};
