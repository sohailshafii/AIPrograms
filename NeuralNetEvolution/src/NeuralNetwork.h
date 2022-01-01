// https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#pragma once

#include "Individual.h"
#include <array>

class NeuralNetwork {
public:
	NeuralNetwork(int numInput, int numHidden,
		int numOutput);

	void SetWeights(double *bestWeights);
	double* GetWeights();

	void ComputeOutputs(double* xValues, double* outputs) const;
	double* Train(double** trainData, int numTrainData, int popSize,
		int maxGeneration, double exitError, double mutateRate, 
		double mutateChange, double tau);

	Individual* Select(int n, Individual* population,
		int popSize, double tau);
	Individual* Reproduce(const Individual& parent1,
		const Individual& parent2, double minGene,
		double maxGene, double mutateRate, double mutateChange);

	void Mutate(const Individual &child, double maxGene,
		double mutateRate, double mutateChange);

	double GetAccuracy(double **testData, int numTestData) const;

private:
	static double** MakeMatrix(int rows, int cols);
	static double HyperTanFunction(double x);
	static double* SoftMax(double* oSums);

	static void Place(const Individual &child1,
		const Individual& child2, Individual* population,
		int popSize);
	double MeanSquaredError(double** trainData, int numTrainData,
		double* weights);

	static int MaxIndex(double* vector, int vectorLength);

	int numInput;
	int numHidden;
	int numOutput;
	double* inputs;
	double** ihWeights;
	double* hBiases;
	double* hOutputs;
	double** hoWeights;
	double* oBiases;
	double* outputs;
};
