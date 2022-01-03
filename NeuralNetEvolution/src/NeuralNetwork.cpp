// https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#include "NeuralNetwork.h"
#include "Common.h"
#include <limits>
#include <iostream>
#include <algorithm>
#include <cmath>

NeuralNetwork::NeuralNetwork(int numInput, int numHidden,
	int numOutput) {
	this->numInput = numInput;
	this->numHidden = numHidden;
	this->numOutput = numOutput;
	inputs = new double[numInput];
	ihWeights = MakeMatrix(numInput, numHidden);
	hBiases = new double[numHidden];
	hOutputs = new double[numHidden];
	hoWeights = MakeMatrix(numHidden, numOutput);
	oBiases = new double[numOutput];
	outputs = new double[numOutput];
}

void NeuralNetwork::SetWeights(double *bestWeights) {
	// set weights and biases from weights
	auto numWeights = GetNumWeights();

	// points into weights param
	int k = 0;
	for (int i = 0; i < numInput; i++) {
		for (int j = 0; j < numHidden; j++) {
			ihWeights[i][j] = bestWeights[k++];
		}
	}

	for (int i = 0; i < numHidden; i++) {
		hBiases[i] = bestWeights[k++];
	}

	for (int i = 0; i < numHidden; i++) {
		for (int j = 0; j < numOutput; j++) {
			hoWeights[i][j] = bestWeights[k++];
		}
	}

	for (int i = 0; i < numOutput; i++) {
		oBiases[i] = bestWeights[k++];
	}
}

double* NeuralNetwork::GetWeights() {
	int numWeights = GetNumWeights();
	double* result = new double[numWeights];
	int k = 0;
	for (int i = 0; i < numInput; i++) {
		for (int j = 0; j < numHidden; j++) {
			result[k++] = ihWeights[i][j];
		}
	}

	for (int i = 0; i < numHidden; i++) {
		result[k++] = hBiases[i];
	}

	for (int i = 0; i < numHidden; i++) {
		for (int j = 0; j < numOutput; j++) {
			result[k++] = hoWeights[i][j];
		}
	}

	for (int i = 0; i < numOutput; i++) {
		result[k++] = oBiases[i];
	}

	return result;
}

void NeuralNetwork::ComputeOutputs(double* xValues, double *yValues) const {
	// feed-forward mechanism for NN classifier
	// xValues has numInput values, outputs has numOutputs values

	// TODO cache arrays
	double* hSums = new double[numHidden];
	double* oSums = new double[numOutput];

	for (int i = 0; i < numInput; i++) {
		inputs[i] = xValues[i];
	}

	for (int j = 0; j < numHidden; j++) {
		hSums[j] = 0.0;
		for (int i = 0; i < numInput; i++) {
			hSums[j] += inputs[i] * ihWeights[i][j];
		}
	}

	for (int i = 0; i < numHidden; i++) {
		hSums[i] += hBiases[i];
		hOutputs[i] = HyperTanFunction(hSums[i]);
	}

	for (int j = 0; j < numOutput; j++) {
		oSums[j] = 0.0;
		for (int i = 0; i < numHidden; i++) {
			oSums[j] += hOutputs[i] * hoWeights[i][j];
		}
	}

	for (int i = 0; i < numOutput; i++) {
		oSums[i] += oBiases[i];
	}

	// TODO: cache
	double* softOut = SoftMax(oSums);
	memcpy(outputs, softOut, numOutput * sizeof(double));
	memcpy(yValues, outputs, numOutput * sizeof(double));

	delete[] softOut;
}

double* NeuralNetwork::Train(double** trainData, int numTrainData,
	int popSize, int maxGeneration, double exitError, double mutateRate,
	double mutateChange, double tau, int & numWeights) {
	// use evolutionary optimization to train NN
	numWeights = GetNumWeights();

	double minX = -10.0;
	double maxX = 10.0;

	// TODO: caching
	Individual* population = new Individual[popSize];
	double* bestSolution = new double[numWeights];
	double bestError = std::numeric_limits<double>::max();

	for (int i = 0; i < popSize; i++) {
		population[i] = Individual(numWeights,
			minX, maxX, mutateRate, mutateChange);
		double error = MeanSquaredError(trainData,
			numTrainData, population[i].chromosome);
		population[i].error = error;

		if (population[i].error < bestError) {
			bestError = population[i].error;
			memcpy(bestSolution, population[i].chromosome,
				numWeights * sizeof(double));
		}
	}

	// main EO processing loop
	int gen = 0; bool done = false;
	while (gen < maxGeneration && done == false) {
		// TODO: caching
		Individual* parents = Select(2, population, popSize, tau);
		Individual* children = Reproduce(parents[0],
			parents[1], minX, maxX, mutateRate,
			mutateChange);
		delete[] parents;

		children[0].error = MeanSquaredError(trainData,
			numTrainData, children[0].chromosome);
		children[1].error = MeanSquaredError(trainData,
			numTrainData, children[1].chromosome);

		Place(children[0], children[1], population, popSize);
		delete[] children;

		Individual immigrant(numWeights, minX, maxX,
			mutateRate, mutateChange);
		immigrant.error = MeanSquaredError(trainData,
			numTrainData, immigrant.chromosome);
		population[popSize - 3] = immigrant; // third worst

		for (int i = popSize - 3; i < popSize; ++i) {
			if (population[i].error < bestError) {
				bestError = population[i].error;
				memcpy(bestSolution, population[i].chromosome,
					numWeights * sizeof(double));
				if (bestError < exitError) {
					done = true;
					std::cout << "\nEarly exit at generation: " << gen << std::endl;
				}
			}
		}
		++gen;
	}

	delete[] population;

	return bestSolution;
}

Individual* NeuralNetwork::Select(int n, Individual* population,
	int popSize, double tau) {
	// TODO: cache
	int* indices = new int[popSize];
	for (int i = 0; i < popSize; i++) {
		indices[i] = i;
	}

	for (int i = 0; i < popSize; i++) {
		int r = (int)(randVal()*popSize);
		int tmp = indices[r];
		indices[r] = indices[i];
		indices[i] = tmp;
	}

	int tournSize = (int)(tau * popSize);
	if (tournSize < n) {
		tournSize = n;
	}
	// TODO: cache
	Individual* candidates = new Individual[tournSize];

	for (int i = 0; i < tournSize; i++) {
		candidates[i] = population[indices[i]];
	}
	std::sort(candidates, candidates + tournSize,
		[](const Individual &one, const Individual &two) { 
		return one.error <= two.error;
	});

	std::cout << "candidates, sorted: ";
	for (int i = 0; i < tournSize; i++) {
		std::cout << candidates[i].error << " ";
	}
	std::cout << std::endl;

	Individual *results = new Individual[n];
	for (int i = 0; i < n; i++) {
		results[i] = candidates[i];
	}

	delete[] indices;
	delete[] candidates;
	return results;
}

Individual* NeuralNetwork::Reproduce(Individual const & parent1,
	Individual const & parent2, double minGene,
	double maxGene, double mutateRate, double mutateChange) {
	int numGenes = parent1.numGenes;
	// crossover point: 0 means "between 0 and 1"
	int cross = (int)(randVal()*(numGenes-1));
	Individual child1(numGenes, minGene,
		maxGene, mutateRate, mutateChange);
	Individual child2(numGenes, minGene,
		maxGene, mutateRate, mutateChange);

	for (int i = 0; i <= cross; ++i) {
		child1.chromosome[i] = parent1.chromosome[i];
	}
	for (int i = cross + 1; i < numGenes; ++i) {
		child2.chromosome[i] = parent1.chromosome[i];
	}

	for (int i = 0; i <= cross; ++i) {
		child2.chromosome[i] = parent2.chromosome[i];
	}
	for (int i = cross + 1; i < numGenes; ++i) {
		child1.chromosome[i] = parent2.chromosome[i];
	}

	Mutate(child1, maxGene, mutateRate, mutateChange);
	Mutate(child2, maxGene, mutateRate, mutateChange);

	Individual* result = new Individual[2];
	result[0] = child1;
	result[1] = child2;

	return result;
}

void NeuralNetwork::Mutate(const Individual &child, double maxGene,
	double mutateRate, double mutateChange) {
	double hiVal = mutateChange * maxGene;
	double loVal = -hiVal;
	for (int i = 0; i < child.numGenes; i++) {
		if (randVal() < mutateRate) {
			double delta = (hiVal - loVal)*randVal() + loVal;
			child.chromosome[i] += delta;
		}
	}
}

double NeuralNetwork::GetAccuracy(double **testData, int numTestData) const {
	// percentage correct using winner takes all
	int numCorrect = 0;
	int numWrong = 0;
	// again, this is stupid and I wish the original tutorial didn't allocate
	// so much
	double *xValues = new double[numInput];
	double *tValues = new double[numOutput];
	double *yValues = new double[numOutput];

	for (int i = 0; i < numTestData; ++i) {
		memcpy(xValues, testData[i], numInput * sizeof(double));
		memcpy(tValues, &testData[i][numInput], numOutput * sizeof(double));

		ComputeOutputs(xValues, yValues);

		int maxIndex = MaxIndex(yValues, numOutput);
		
		if (tValues[maxIndex] == 1.0) {
			++numCorrect;
		}
		else {
			++numWrong;
		}
	}

	delete[] xValues;
	delete[] tValues;
	delete[] yValues;

	return ((double)numCorrect + 1.0)/
		(double)(numCorrect + numWrong);
}

double** NeuralNetwork::MakeMatrix(int rows, int cols) {
	double** result = new double* [rows];
	for (int r = 0; r < rows; ++r) {
		result[r] = new double[cols];
	}
	return result;
}

double NeuralNetwork::HyperTanFunction(double x) {
	if (x < -20.0) {
		return -1.0f;
	}
	else if (x > 20.0f) {
		return 1.0f;
	}
	
	return  tanh(x);
}

// TODO cache result to avoid excess allocations
double* NeuralNetwork::SoftMax(double* oSums) const {
	double max = oSums[0];
	for (int i = 0; i < numOutput; i++) {
		if (oSums[i] > max) {
			max = oSums[i];
		}
	}

	// determine scaling factor
	double scale = 0.0;
	for (int i = 0; i < numOutput; i++) {
		scale += exp(oSums[i] - max);
	}

	double* result = new double[numOutput];
	for (int i = 0; i < numOutput; i++) {
		result[i] = exp(oSums[i] - max) / scale;
	}

	// scaled so xi sum to 1.0
	return result;
}

void NeuralNetwork::Place(const Individual &child1,
	const Individual& child2, Individual* population,
	int popSize) {
	std::sort(population,
		population + popSize,
		[](const Individual& a, const Individual& b) {
		return a.error < b.error;
	});
	population[popSize - 1] = child1;
	population[popSize - 2] = child2;
}

double NeuralNetwork::MeanSquaredError(double** trainData,
	int numTrainData, double* weights) {
	SetWeights(weights);

	// TODO: caching, bad to allocate junk
	double* xValues = new double[numInput]; // inputs
	double* tValues = new double[numOutput]; // targets
	double sumSquaredError = 0.0;
	double *yValues = new double[numOutput];
	for (int i = 0; i < numTrainData; ++i) {
		// assume data has x-vals followed by y-vals
		memcpy(xValues, trainData[i], numInput * sizeof(double));
		memcpy(tValues, &trainData[i][numInput], numOutput * sizeof(double));
		this->ComputeOutputs(xValues, yValues);
		for (int j = 0; j < numOutput; ++j) {
			double yDiff = yValues[j] - tValues[j];
			sumSquaredError += yDiff*yDiff;
		}
	}

	delete[] xValues;
	delete[] tValues;
	delete[] yValues;

	return sumSquaredError/(double)numTrainData;
}

int NeuralNetwork::MaxIndex(double* vector, int vectorLength) {
	int bigIndex = 0;
	double biggestVal = vector[0];

	for (int i = 1; i < vectorLength; ++i) {
		if (vector[i] > biggestVal) {
			biggestVal = vector[i];
			bigIndex = i;
		}
	}

	return bigIndex;
}

