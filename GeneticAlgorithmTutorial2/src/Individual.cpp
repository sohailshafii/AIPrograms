// http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#include "Individual.h"

int Individual::defaultGeneLength = 64;

std::mt19937 *Individual::gen; 
std::uniform_real_distribution<> *Individual::dis;

Individual::Individual() {
	allocateRandData();

	genes = new char[defaultGeneLength];
	numGenes = defaultGeneLength;
	fitness = 0;
}

Individual::~Individual() {
	if (genes != nullptr) {
		delete [] genes;
	}
}

Individual::Individual(const Individual &p2) {
	allocateAndCopyFrom(p2);
}

Individual& Individual::operator=(
	const Individual& other) {
	if (this != &other) {
		allocateAndCopyFrom(other);
	}
	return *this;
}

void Individual::allocateAndCopyFrom(
	const Individual& other) {
	genes = new char[other.numGenes];
	memcpy(genes, other.genes, other.numGenes);
	numGenes = other.numGenes;
	fitness = other.fitness;
}

void Individual::generateIndividual() {
	for (int i = 0; i < numGenes; i++) {
		char gene = (char)(255.0f*Individual::randUnitVal());
	}
}

std::string Individual::toString() const {
	std::string geneString = "";
    for (int i = 0; i < size(); i++) {
        geneString += genes[i];
    }
    return geneString;
}

void Individual::allocateRandData() {
	if (gen != nullptr) {
		return;
	}
	// Will be used to obtain a seed for the random number engine
	std::random_device rd;  
	// Standard mersenne_twister_engine seeded with rd()
	gen = new std::mt19937(rd());
	dis = new std::uniform_real_distribution<>(0.0f, 1.0f);
}

float Individual::randUnitVal() {
	return (*dis)(*gen);
}
