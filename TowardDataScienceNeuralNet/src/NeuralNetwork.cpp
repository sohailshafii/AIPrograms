//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#include "NeuralNetwork.h"
#include <cmath>
#include <iostream>
#include "Common.h"

NeuralNetwork::NeuralNetwork(float **x, float *y,
	int numRows, int numColumns) {
	this->numRows = numRows;
	this->numColumns = numColumns;

	this->input = new float*[numRows];
	this->weights1 = new float*[numColumns];
	this->weights2 = new float[numRows];

	this->y = new float[numRows];
	this->output = new float[numRows];

	this->layer1 = new float[numRows];

	this->dWeights1 = new float*[numColumns];
	this->dWeights2 = new float[numRows];

	for (int row = 0; row < numRows; row++) {
		this->input[row] = new float[numColumns];
		for(int column = 0; column < numColumns; column++) {
			this->input[row][column] = x[row][column];
		}
		this->y[row] = y[row];
		this->output[row] = randomUnitValue();
		this->weights2[row] = randomUnitValue();
	}

	for (int column = 0; column < numColumns; column++) {
		this->weights1[column] = new float[numRows];
		this->dWeights1[column] = new float[numRows];
		for (int row = 0; row < numRows; row++) {
			this->weights1[column][row] = randomUnitValue();
		}
	}
}

NeuralNetwork::~NeuralNetwork() {
	if (this->input != nullptr) {
		for (int row = 0; row < numRows; row++) {
			delete [] this->input[row];
		}
		delete [] this->input;
	}
	if (this->weights1 != nullptr) {
		for (int row = 0; row < numColumns; row++) {
			delete [] this->weights1[row];
		}
		delete [] this->weights1;
	}

	if (this->weights2 != nullptr) {
		delete [] this->weights2;
	}
	if (this->y != nullptr) {
		delete [] this->y;
	}
	if (this->output != nullptr) {
		delete [] this->output;
	}
	if (this->layer1 != nullptr) {
		delete [] this->layer1;
	}

	if (dWeights1 != nullptr) {
		for (int column = 0;
			column < numColumns; column++) {
			delete [] this->dWeights1[column];
		}
		delete [] this->dWeights1;
	}
	if (dWeights2 != nullptr) {
		delete [] dWeights2;
	}
}

void NeuralNetwork::configure(int iterations) {
	std::cout << "Input:\n";
	for (int row = 0; row < numRows; row++) {
		auto inputRow = input[row];
		for (int column = 0; column < numColumns; column++) {
			std::cout << inputRow[column] << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Y: ";
	for (int row = 0; row < numRows; row++) {
		std::cout << y[row] << ", ";
	}
	std::cout << std::endl;

	for (int i = 0; i < iterations; i++) {
		feedForward();
		//backProp();
	} 

	std::cout << "After " << iterations << 
		" iterations, output is:\n";
	for (int row = 0; row < numRows; row++) {
		std::cout << output[row] << ", ";
	}
	std::cout << std::endl;
	//std::cout << "\nCurrent loss: "
//		<< computeCurrentLoss() << ".\n";
}

void NeuralNetwork::feedForward() {
	/*for (int i = 0; i < arraySize; i++) {
		this->layer1[i] = sigmoid(this->input[i] * this->weights1[i]);
		this->output[i] = sigmoid(this->layer1[i] * this->weights2[i]);
	}*/

	// compute first layer
	for (int row = 0; row < numRows; row++) {
		auto inputRow = input[row];
		float dotProduct = 0.0f;
		for (int column = 0; column; column++) {
			dotProduct = inputRow[column] *
				weights1[column][row];
		}
		layer1[row] = sigmoid(dotProduct);
	}

	// and now second layer
	for (int row = 0; row < numRows; row++) {
		output[row] = sigmoid(layer1[row] * weights2[row]);
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
	for (int row = 0; row < numRows; row++) {
		float diff = this->output[row] - y[row];
		loss += diff*diff;
	}
	return loss;
}

/*void NeuralNetwork::backProp() {
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
}*/

