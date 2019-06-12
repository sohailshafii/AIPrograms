// // https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#include "Individual.h"
#include "Common.h"
#include <cstring>

Individual::Individual() {
	chromosome = nullptr;
}

Individual::Individual(int numGenes, double minGene, double maxGene,
	double mutateRate, double mutateChange) {
	this->numGenes = numGenes;
	this->minGene = minGene;
	this->maxGene = maxGene;
	this->mutateRate = mutateRate;
	this->mutateChange = mutateChange;

	this->chromosome = new double[numGenes];
	double chromosomeRange = maxGene - minGene;
	for (int geneIndex = 0; geneIndex < numGenes; geneIndex++) {
		this->chromosome[geneIndex] = chromosomeRange*randVal()+
			minGene;
	}
}

Individual::Individual(const Individual &p2) {
	AllocateAndCopyFrom(p2);
	minGene = p2.minGene;
	maxGene = p2.maxGene;
	mutateRate = p2.mutateRate;
	mutateChange = p2.mutateChange;
	error = p2.error;
}

Individual& Individual::operator=(const Individual& other) {
	if (this != &other) {
		if (this->numGenes != other.numGenes) {
			if (chromosome != nullptr) {
				delete[] chromosome;
			}
			AllocateAndCopyFrom(other);
		}
		else {
			memcpy(chromosome, other.chromosome, sizeof(double)*other.numGenes);
		}
	}

	minGene = other.minGene;
	maxGene = other.maxGene;
	mutateRate = other.mutateRate;
	mutateChange = other.mutateChange;
	error = other.error;
	return *this;
}

Individual::~Individual() {
	if (chromosome != nullptr) {
		delete[] chromosome;
	}
}

void Individual::AllocateAndCopyFrom(const Individual& other) {
	chromosome = new double[other.numGenes];
	numGenes = other.numGenes;
	memcpy(chromosome, other.chromosome, sizeof(double)*other.numGenes);
}

// TODO: comparator
