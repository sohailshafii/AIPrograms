// https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#include "NeuralNetwork.h"
#include "Common.h"
#include <limits>
#include <iostream>

NeuralNetwork::NeuralNetwork(int numInput, int numHidden,
	int numOutput) {
	// TODO
}

void NeuralNetwork::SetWeights(double *bestWeights) {

}

double* NeuralNetwork::GetWeights() {
	return nullptr;
}

void NeuralNetwork::ComputeOutputs(double* xValues, double *outputs) const {
	
}

double* NeuralNetwork::Train(double** trainData, int numTrainData,
	int popSize, int maxGeneration, double exitError, double mutateRate,
	double mutateChange, double tau) {
	// use evolutionary optimization to train NN
	int numWeights = numInput * numHidden +
		numHidden * numOutput + numHidden +
		numOutput;

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

Individual* NeuralNetwork::Reproduce(const Individual& parent1,
	const Individual& parent2, double minGene,
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
		memcpy(tValues, &testData[i][numInput], numOutput);

		ComputeOutputs(xValues, yValues);

		int maxIndex = MaxIndex(yValues);
		
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
	return nullptr;
}

double NeuralNetwork::HyperTanFunction(double x) {
	return 0.0;
}

double* NeuralNetwork::SoftMax(double* oSums) {
	return nullptr;
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

	for (int i = 0; i < vectorLength; ++i) {
		if (vector[i] > biggestVal) {
			biggestVal = vector[i];
			bigIndex = i;
		}
	}

	return bigIndex;
	return 0;
}

