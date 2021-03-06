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
	this->layer1Derivs = new Matrix(*layer1);
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
	if (layer1Derivs != nullptr) {
		delete layer1Derivs;
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
	// compute partial deriv weights 2
	auto numRows = tempOutput->getNumRows();
	for (int row = 0; row < numRows; row++) {
		(*tempOutput)[row][0] = 
			2.0f*((*y)[row][0]-(*output)[row][0])*
			derivSigmoid((*output)[row][0]);
	}
	*dWeights2 = layer1->transpose()*(*tempOutput);

	Matrix tempMult = (*tempOutput)*(weights2->transpose());
	numRows = layer1Derivs->getNumRows();
	auto numCols = layer1Derivs->getNumColumns();
	for (int row = 0; row < numRows; row++) {
		auto currRow = (*layer1Derivs)[row];
		auto currRowLayer1 = (*layer1)[row];
		auto tempMultRow = tempMult[row];

		for (int col = 0; col < numCols; col++) {
			currRow[col] = derivSigmoid(currRowLayer1[col]);
			tempMultRow[col] *= currRow[col];
		}
	}
	*dWeights1 = input->transpose()*tempMult;

	(*weights2) += (*dWeights2);
	(*weights1) += (*dWeights1);
}
