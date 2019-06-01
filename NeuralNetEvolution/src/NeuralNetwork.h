// https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#pragma once

class NeuralNetwork {
public:

	NeuralNetwork(int numInput, int numHidden,
		int numOutput);

	void Train(double** trainData, int popSize, int maxGeneration,
		double exitError, double mutateRate, double mutateChange,
		double tau, double **bestWeightsToSet);

	void SetWeights(double *bestWeights);
	double GetAccuracy(double **testData) const;

private:

};
