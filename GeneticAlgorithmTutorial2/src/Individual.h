// http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#pragma once

#include <string>
#include <random>
#include "FitnessCalc.h"

class Individual {
public:
	Individual();
	~Individual();

	Individual(const Individual &p2);
	Individual& operator=(
		const Individual& other);

	void generateIndividual();

	static void setDefaultGeneLength(int length) {
		defaultGeneLength = length;
	}

	int getGene(int index) const {
		return genes[index];
	}

	void setGene(int index, int value) {
		genes[index] = value;
		fitness = 0;
	}

	int size() const {
		return numGenes;
	}

	int getFitness() {
		if (fitness == 0) {
			fitness = FitnessCalc::getFitness(*this);
		}
		return fitness;
	}

	void print() const;

private:
	void allocateAndCopyFrom(const Individual& other);
	void copyFrom(const Individual& other);
	//void allocateRandData();

	static float randUnitVal();

	static int defaultGeneLength;
	int* genes;
	int numGenes;
	int fitness;

	//static std::mt19937 *gen; 
	//static std::uniform_real_distribution<> *dis;
};
