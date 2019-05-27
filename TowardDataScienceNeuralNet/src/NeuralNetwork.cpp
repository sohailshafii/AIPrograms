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
	this->output = new Matrix(y);
	this->output->fillWithZeros();

	this->layer1 = new Matrix(x.getNumRows(), x.getNumRows());

	this->dWeights1 = new Matrix(x.getNumColumns(),
		x.getNumRows());
	this->dWeights2 = new Matrix(x.getNumRows(), 1);
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
}

/*void NeuralNetwork::configure(int iterations) {
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
		backProp();
	} 

	std::cout << "After " << iterations << 
		" iterations, output is:\n";
	for (int row = 0; row < numRows; row++) {
		std::cout << output[row] << ", ";
	}
	std::cout << std::endl;
	std::cout << "\nCurrent loss: "
		<< computeCurrentLoss() << ".\n";
}

void NeuralNetwork::feedForward() {
	int numRowsLayer1 = numRows;
	int numColumnsLayer1 = numColumns;
	// compute first layer
	for (int row = 0; row < numRowsLayer1; row++) {
		auto inputRow = input[row];
		// note that layer1 is symmetric
		for (int column = 0; column < numColumnsLayer1; column++) {
			float dotProduct = 0.0f;
			for (int dotIndex = 0; dotIndex < numColumns;
				dotIndex++) {
				dotProduct = inputRow[dotIndex] *
					weights1[dotIndex][column];
			}
			layer1[row][column] = sigmoid(dotProduct);
		}
	}

	// and now second layer
	for (int row = 0; row < numRows; row++) {
		float dotProduct = 0.0f;
		auto layer1Row = layer1[row];
		for (int dotIndex = 0; dotIndex < numRows; dotIndex++) {
			dotProduct += layer1Row[dotIndex]*weights2[dotIndex];
		}
		output[row] = sigmoid(dotProduct);
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

void NeuralNetwork::backProp() {
	
	for (int row = 0; row < numRows; row++) {
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
//}

