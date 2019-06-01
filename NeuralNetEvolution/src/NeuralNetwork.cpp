// https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int numInput, int numHidden,
	int numOutput) {

}


void NeuralNetwork::Train(double** trainData, int popSize, int maxGeneration,
	double exitError, double mutateRate, double mutateChange,
	double tau, double **bestWeightsToSet) {

}

void NeuralNetwork::SetWeights(double *bestWeights) {

}

double NeuralNetwork::GetAccuracy(double **testData) const {
	// TODO
	return 0.0;
}
