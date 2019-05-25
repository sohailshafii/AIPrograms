//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#include "NeuralNetwork.h"
#include <cmath>
#include "Common.h"

NeuralNetwork::NeuralNetwork(float *x, float *y,
	int arraySize) {
	this->arraySize = arraySize;

	this->input = new float[arraySize];
	this->y = new float[arraySize];
	this->weights1 = new float[arraySize];
	this->weights2 = new float[arraySize];
	this->output = new float[arraySize];

	this->layer1 = new float[arraySize];

	for (int i = 0; i < arraySize; i++) {
		this->input[i] = x[i];
		this->weights1[i] = randomUnitValue();
		this->weights2[i] = randomUnitValue();
		this->y[i] = y[i];
		this->output[i] = 0.0f;
	}
}

NeuralNetwork::~NeuralNetwork() {
	if (input != nullptr) {
		delete [] input;
	}
	if (weights1 != nullptr) {
		delete [] weights1;
	}
	if (weights2 != nullptr) {
		delete [] weights2;
	}
	if (y != nullptr) {
		delete [] y;
	}
	if (output != nullptr) {
		delete [] output;
	}

	if (layer1 != nullptr) {
		delete [] layer1;
	}
}

void NeuralNetwork::feedForward() {
	for (int i = 0; i < arraySize; i++) {
		this->layer1[i] = sigmoid(this->input[i] * this->weights1[i]);
		this->output[i] = sigmoid(this->layer1[i] * this->weights2[i]);
	}
}

float NeuralNetwork::sigmoid(float x) {
	return (1.0f/(1.0f + exp(-x)));
}
