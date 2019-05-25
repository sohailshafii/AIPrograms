//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#include "NeuralNetwork.h"
#include <cmath>
#include <iostream>
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
	this->dWeights1 = new float[arraySize];
	this->dWeights2 = new float[arraySize];

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

	if (dWeights1 != nullptr) {
		delete [] dWeights1;
	}
	if (dWeights2 != nullptr) {
		delete [] dWeights2;
	}
}

void NeuralNetwork::configure(int iterations) {
	std::cout << "Input: ";
	for (int i = 0; i < arraySize; i++) {
		std::cout << input[i] << ", ";
	}
	std::cout << std::endl;
	std::cout << "Y: ";
	for (int i = 0; i < arraySize; i++) {
		std::cout << y[i] << ", ";
	}
	std::cout << std::endl;

	for (int i = 0; i < iterations; i++) {
		feedForward();
		backProp();
	} 

	std::cout << "After " << iterations << 
		" iterations, output is:\n";
	for (int i = 0; i < arraySize; i++) {
		std::cout << output[i] << ", ";
	}
	std::cout << "\nCurrent loss: "
		<< computeCurrentLoss() << ".\n";
}

void NeuralNetwork::feedForward() {
	for (int i = 0; i < arraySize; i++) {
		this->layer1[i] = sigmoid(this->input[i] * this->weights1[i]);
		this->output[i] = sigmoid(this->layer1[i] * this->weights2[i]);
	}
}

float NeuralNetwork::sigmoid(float x) const {
	return (1.0f/(1.0f + exp(-x)));
}

float NeuralNetwork::derivSigmoid(float x) const {
	auto sigmoidVal = sigmoid(x);
	return sigmoidVal*(1.0f - sigmoidVal);
}

// note that output y_hat = 
// sigmoid(weights2*layer1 + biases_2)
// and layer1 = Weights1*input + biases_1
// which is a 2-layer neural network
// we have to find the minimum of the loss function
// so we need to take the derivative of what's inside
// the sum, which is (y_hat - y)^2 per neural bit
float NeuralNetwork::computeCurrentLoss() const {
	float loss = 0.0f;
	for (int i = 0; i < arraySize; i++) {
		float diff = this->output[i] - y[i];
		loss += diff*diff;
	}
	return loss;
}

void NeuralNetwork::backProp() {
	for (int i = 0; i < arraySize; i++) {
		float diffYOutput = 2.0*(y[i] - output[i]);
		float derivSigmoidOutTerm = 
			diffYOutput * derivSigmoid(output[i]);

		weights2[i] = derivSigmoidOutTerm * layer1[i];
		weights1[i] = derivSigmoidOutTerm
			* weights2[i] * derivSigmoid(layer1[i])
			* input[i];

		// use partial derivatives to (hopefully) move toward minimum
		weights1[i] += dWeights1[i];
		weights2[i] += dWeights2[i];
	}
}

