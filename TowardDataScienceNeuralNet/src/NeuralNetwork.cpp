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

	this->layer1 = new float*[numRows];

	this->dWeights1 = new float*[numColumns];
	this->dWeights2 = new float[numRows];

	for (int row = 0; row < numRows; row++) {
		this->input[row] = new float[numColumns];
		this->layer1[row] = new float[numRows];

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
		for (int column = 0; column < numColumns; column++) {
			delete [] this->weights1[column];
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
		for (int row = 0; row < numRows; row++) {
			delete [] this->layer1[row];
		}
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
	}
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

