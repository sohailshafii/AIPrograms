// https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#pragma once

#include "Individual.h"
#include <array>

class NeuralNetwork {
public:
	NeuralNetwork(int numInput, int numHidden,
		int numOutput);
	~NeuralNetwork();

	void SetWeights(double *bestWeights);
	double* GetWeights();

	void ComputeOutputs(double* xValues, double* yValues) const;
	double* Train(double** trainData, int numTrainData, int popSize,
		int maxGeneration, double exitError, double mutateRate, 
		double mutateChange, double tau, int& numWeights);

	void Select(int n, Individual* population,
		int popSize, double tau, int* indices, Individual* candidates,
		int tournSize, Individual* results);
	void Reproduce(Individual const & parent1,
		Individual const & parent2, double minGene,
		double maxGene, double mutateRate, double mutateChange,
		Individual* results);

	void Mutate(const Individual &child, double maxGene,
		double mutateRate, double mutateChange);

	double GetAccuracy(double **testData, int numTestData) const;

private:
	static double** MakeMatrix(int rows, int cols);
	static double HyperTanFunction(double x);
	void SoftMax(double* oSums) const;

	static void Place(const Individual &child1,
		const Individual& child2, Individual* population,
		int popSize);
	double MeanSquaredError(double** trainData, int numTrainData,
		double* weights, double* xValues,
		double* yValues, double* tValues);

	static int MaxIndex(double* vector, int vectorLength);

	int GetNumWeights() const {
		return numInput * numHidden +
			numHidden * numOutput + numHidden +
			numOutput;
	}

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

	double* softMaxResult;
	double* hSums;
	double* oSums;
};
