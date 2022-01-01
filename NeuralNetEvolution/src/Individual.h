œ// https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#pragma once

class Individual {
public:
	Individual();
	Individual(int numGenes, double minGene, double maxGene,
		double mutateRate, double mutateChange);

	Individual(const Individual &p2);
	Individual& operator=(const Individual& other);

	~Individual();

	double* chromosome;
	double error;
	int numGenes;

private:
	void AllocateAndCopyFrom(const Individual& other);

	// smallest value for a chromosome
	double minGene;
	double maxGene;
	double mutateRate;
	double mutateChange;
};
