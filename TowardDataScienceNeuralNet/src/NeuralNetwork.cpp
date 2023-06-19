//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#include "NeuralNetwork.h"
#include <cmath>
#include <iostream>
#include "Common.h"

NeuralNetwork::NeuralNetwork(Matrix const & x, Matrix const & y) {
	// assuming x is 4x3...and y is 4x1 for comments regarding
	// matrix sizes below.
	this->input = new Matrix(x);
	// weights1 is 3x4
	this->weights1 = new Matrix(x.GetNumColumns(),
		x.GetNumRows());
	this->weights1->FillWithRandomValues(0.0f, 1.0f);

	// weights2 is 4x1
	this->weights2 = new Matrix(x.GetNumRows(), 1);
	this->weights2->FillWithRandomValues(0.0f, 1.0f);

	// y is 4x1
	this->y = new Matrix(y);
	// 4x1
	this->output = new Matrix(x.GetNumRows(), 1);
	this->output->FillWithZeros();

	// 4x4
	this->layer1 = new Matrix(x.GetNumRows(), x.GetNumRows());

	// 3x3, for derivatives
	this->dWeights1 = new Matrix(x.GetNumColumns(),
		x.GetNumRows());
	// 4x1, fore derivatives
	this->dWeights2 = new Matrix(x.GetNumRows(), 1);

	// 4x1
	this->tempOutput = new Matrix(*output);
	// 4x4
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

void NeuralNetwork::Configure(int iterations) {
	std::cout << "Input:\n";
	input->Print();
	std::cout << std::endl;
	std::cout << "Y: ";
	y->Print();

	for (int i = 0; i < iterations; i++) {
		FeedForward();
		BackProp();
	} 

	std::cout << "Output:\n";
	output->Print();
	std::cout << "\nCurrent loss: "
		<< ComputeCurrentLoss() << ".\n";
}

void NeuralNetwork::FeedForward() {
	// 4x4 = 4x3 * 3x4, then calculate sigmoid on first layer
	*layer1 = (*input)*(*weights1);
	auto numRows = layer1->GetNumRows();
	auto numCols = layer1->GetNumColumns();
	for (int row = 0; row < numRows; row++) {
		auto currRow = (*layer1)[row];
		for (int col = 0; col < numCols; col++) {
			currRow[col] = Sigmoid(currRow[col]);
		}
	}

	// 4x1 = 4x4 * 4x1, then calculate sigmoid on second layer
	*output = (*layer1)*(*weights2);
	numRows = output->GetNumRows();
	numCols = output->GetNumColumns();
	for (int row = 0; row < numRows; row++) {
		auto currRow = (*output)[row];
		for (int col = 0; col < numCols; col++) {
			currRow[col] = Sigmoid(currRow[col]);
		}
	}
}

float NeuralNetwork::Sigmoid(float x) const {
	return (1.0f/(1.0f + exp(-x)));
}

// in this case, x is the sigmoid value
float NeuralNetwork::DerivSigmoid(float x) const {
	return x * (1.0f - x);
}

// note that output y_hat = 
// sigmoid(weights2*layer1 + biases_2)
// and layer1 = Weights1*input + biases_1
// which is a 2-layer neural network
// we have to find the minimum of the loss function
// so we need to take the derivative of what's inside
// the sum, which is (y_hat - y)^2 per neural bit
float NeuralNetwork::ComputeCurrentLoss() const {
	float loss = 0.0f;
	auto numRows = this->output->GetNumRows();
	for (int row = 0; row < numRows; row++) {
		float diff = (*output)[row][0] - (*y)[row][0];
		loss += diff*diff;
	}
	return loss;
}

void NeuralNetwork::BackProp() {
	// compute partial deriv weights 2
	// 4x1. y is our solution, output is what we computed
	// compute derivative of (y - output)^2 to follow
	// gradient descent
	auto numRows = tempOutput->GetNumRows();
	for (int row = 0; row < numRows; row++) {
		(*tempOutput)[row][0] = 
			2.0f*((*y)[row][0]-(*output)[row][0])*
			DerivSigmoid((*output)[row][0]);
	}
	*dWeights2 = layer1->Transpose()*(*tempOutput);

	// as you take derivative of inner layer, first derivative
	// involves multiplying by outer set of weights
	// 4x1 * 1x4 = 4x4
	Matrix tempMult = (*tempOutput)*(weights2->Transpose());
	numRows = layer1Derivs->GetNumRows();
	auto numCols = layer1Derivs->GetNumColumns();
	for (int row = 0; row < numRows; row++) {
		auto currRowDeriv = (*layer1Derivs)[row];
		auto currRowLayer1 = (*layer1)[row];
		auto tempMultRow = tempMult[row];

		for (int col = 0; col < numCols; col++) {
			currRowDeriv[col] = DerivSigmoid(currRowLayer1[col]);
			tempMultRow[col] *= currRowDeriv[col];
		}
	}
	// 3x4 * 4x4 = 3x4
	*dWeights1 = input->Transpose()*tempMult;

	// weights2 => 4x1, weights1 = 3x4
	(*weights2) += (*dWeights2);
	(*weights1) += (*dWeights1);
}
