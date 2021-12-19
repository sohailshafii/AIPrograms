// http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#pragma once

#include <string>
#include <random>
#include "FitnessCalc.h"

class Individual {
public:
	Individual();
	~Individual();

	Individual(Individual  const & p2);
	Individual& operator=(Individual const & other);

	void GenerateIndividual();

	static void SetDefaultGeneLength(int length) {
		defaultGeneLength = length;
	}

	int GetGene(int index) const {
		return genes[index];
	}

	void SetGene(int index, int value) {
		genes[index] = value;
		fitness = 0;
	}

	int Size() const {
		return numGenes;
	}

	int GetFitness() {
		if (fitness == 0) {
			fitness = FitnessCalc::GetFitness(*this);
		}
		return fitness;
	}

	void Print() const;

private:
	void AllocateAndCopyFrom(Individual const & other);
	void CopyFrom(Individual const & other);
	//void allocateRandData();

	static float RandUnitVal();

	static int defaultGeneLength;
	int* genes;
	int numGenes;
	int fitness;

	//static std::mt19937 *gen; 
	//static std::uniform_real_distribution<> *dis;
};
