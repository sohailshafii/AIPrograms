// https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#pragma once

class Individual {
public:
	Individual(int numGenes, double minGene, double maxGene,
		double mutateRate, double mutateChange);

	double* chromosome;
	double error;

private:
	int numGenes;
	// smallest value for a chromosome
	double minGene;
	double maxGene;
	double mutateRate;
	double mutateChange;
};
