//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#include "NeuralNetwork.h"
#include <cmath>
#include <iostream>
#include "Common.h"



NeuralNetwork::NeuralNetwork(const Matrix &x, const Matrix &y) {
	this->input = new Matrix(x);
	this->weights1 = new Matrix(x.getNumColumns(),
		x.getNumRows());
	this->weights1->fillWithRandomValues(0.0f, 1.0f);

	this->weights2 = new Matrix(x.getNumRows(), 1);
	this->weights2->fillWithRandomValues(0.0f, 1.0f);

	this->y = new Matrix(y);
	this->output = new Matrix(x.getNumRows(), 1);
	this->output->fillWithZeros();

	this->layer1 = new Matrix(x.getNumRows(), x.getNumRows());

	this->dWeights1 = new Matrix(x.getNumColumns(),
		x.getNumRows());
	this->dWeights2 = new Matrix(x.getNumRows(), 1);

	this->tempOutput = new Matrix(*output);
}

NeuralNetwork::~NeuralNetwork() {
	if (input != nullptr) {
		delete input;
	}
	if (weights1 != nullptr) {
		delete weights1;
	}
	if (weights2 != nullptr) {
		delete weights2;
	}
	if (y != nullptr) {
		delete y;
	}
	if (output != nullptr) {
		delete output;
	}

	if (layer1 != nullptr) {
		delete layer1;
	}
	if (dWeights1 != nullptr) {
		delete dWeights1;
	}
	if (dWeights2 != nullptr) {
		delete dWeights2;
	}

	if (tempOutput != nullptr) {
		delete tempOutput;
	}
}

void NeuralNetwork::configure(int iterations) {
	std::cout << "Input:\n";
	input->print();
	std::cout << std::endl;
	std::cout << "Y: ";
	y->print();

	for (int i = 0; i < iterations; i++) {
		feedForward();
		backProp();
	} 

	std::cout << "Output:\n";
	output->print();
	std::cout << "\nCurrent loss: "
		<< computeCurrentLoss() << ".\n";
}

void NeuralNetwork::feedForward() {
	*layer1 = (*input)*(*weights1);
	auto numRows = layer1->getNumRows();
	auto numCols = layer1->getNumColumns();
	for (int row = 0; row < numRows; row++) {
		auto currRow = (*layer1)[row];
		for (int col = 0; col < numCols; col++) {
			currRow[col] = sigmoid(currRow[col]);
		}
	}

	*output = (*layer1)*(*weights2);
	numRows = output->getNumRows();
	numCols = output->getNumColumns();
	for (int row = 0; row < numRows; row++) {
		auto currRow = (*output)[row];
		for (int col = 0; col < numCols; col++) {
			currRow[col] = sigmoid(currRow[col]);
		}
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
	auto numRows = this->output->getNumRows();
	for (int row = 0; row < numRows; row++) {
		float diff = (*output)[row][0] - (*y)[row][0];
		loss += diff*diff;
	}
	return loss;
}

void NeuralNetwork::backProp() {
	
	/*for (int row = 0; row < numRows; row++) {
		auto currLayerRow = layer1[row];

		float dotProduct = 0.0f;
		for (int dotIndex = 0; dotIndex < numRows;
			dotIndex++) {
			dotProduct += currLayerRow[dotIndex]
				*2.0f*(y[dotIndex] - output[dotIndex])*
				derivSigmoid(output[dotIndex]);
		}
		dWeights2[row] = dotProduct;
	}

	// weights 2 -- would be nice if we had a matrix class!
	float temp[numRows][numRows];
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numRows;
			col++) {

			float dotProduct = 0.0f;
			for (int dotIndex = 0; dotIndex < numRows;
				dotIndex++) {
				dotProduct += derivSigmoid(output[dotIndex])
					*2.0f*(y[dotIndex] - output[dotIndex])*
					weights2[dotIndex];
			}
			temp[row][col] = dotProduct;
		}
	}*/
	//float temp2[numRows]

	/*for (int i = 0; i < arraySize; i++) {
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
	}*/
}
