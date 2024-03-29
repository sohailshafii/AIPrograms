// http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#include "Individual.h"
#include <cmath>
#include <iostream>

int Individual::defaultGeneLength = 64;

//std::mt19937 *Individual::gen;
//std::uniform_real_distribution<> *Individual::dis;

Individual::Individual() {
	//allocateRandData();
	genes = new int[defaultGeneLength];
	numGenes = defaultGeneLength;
	fitness = 0;
}

Individual::~Individual() {
	if (genes != nullptr) {
		delete[] genes;
	}
}

Individual::Individual(const Individual &p2) {
	AllocateAndCopyFrom(p2);
}

Individual& Individual::operator=(
	const Individual& other) {
	if (this != &other) {
		if (this->numGenes != other.numGenes) {
			if (genes != nullptr) {
				delete[] genes;
			}
			AllocateAndCopyFrom(other);
		}
		else {
			CopyFrom(other);
		}
	}
	return *this;
}

void Individual::AllocateAndCopyFrom(
	const Individual& other) {
	genes = new int[other.numGenes];
	numGenes = other.numGenes;
	CopyFrom(other);
}

void Individual::CopyFrom(const Individual& other) {
	memcpy(genes, other.genes, sizeof(int)*other.numGenes);
	fitness = other.fitness;
}

void Individual::GenerateIndividual() {
	for (int i = 0; i < numGenes; i++) {
		auto randomVar = Individual::RandUnitVal();
		genes[i] = (int)(round(randomVar));
	}
}

void Individual::Print() const {
	for (int i = 0; i < numGenes; i++) {
		std::cout << genes[i] << ", ";
	}
	std::cout << std::endl;
}

/*void Individual::allocateRandData() {
	if (gen != nullptr) {
		return;
	}
	// Will be used to obtain a seed for the random number engine
	std::random_device rd;
	// Standard mersenne_twister_engine seeded with rd()
	gen = new std::mt19937(rd());
	dis = new std::uniform_real_distribution<>(0.0f, 1.0f);
}*/

float Individual::RandUnitVal() {
	//return (*dis)(*gen);
	return (float)rand() / (float)RAND_MAX;
}
