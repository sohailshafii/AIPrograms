// http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#pragma once

#include <string>
#include <random>

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

	char getGene(int index) const {
		return genes[index];
	}

	void setGene(int index, char value) {
		genes[index] = value;
		fitness = 0;
	}

	int size() const {
		return numGenes;
	}

	int getFitness() const {
		// TODO fitness
		return fitness;
	}

	std::string toString() const;

private:
	void allocateAndCopyFrom(const Individual& other);
	void allocateRandData();

	static float randUnitVal();

	static int defaultGeneLength;
	char* genes;
	int numGenes;
	int fitness;

	static std::mt19937 *gen; 
	static std::uniform_real_distribution<> *dis;
};
