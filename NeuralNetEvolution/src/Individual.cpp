// // https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#include "Individual.h"
#include "Common.h"

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
		this->chromosome[i] = chromosomeRange*randVal()+
			minGene;
	}
}
