//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#pragma once

#include "Common.h"
#include "Matrix.h"

// assuming 0 bias, and assume that this is a 
// 2-layer neural network. fine-tuning weights and biases
// for each input is known as "training" a neural network
class NeuralNetwork {
public:
	NeuralNetwork(Matrix const & x, Matrix const & y);
	~NeuralNetwork();

	void Configure(int iterations);

private:
	Matrix *input;
	Matrix *weights1;
	Matrix *weights2;
	Matrix *y;
	Matrix *output;

	Matrix *layer1;
	Matrix *dWeights1;
	Matrix *dWeights2;

	// temp matrices for calculations
	Matrix *tempOutput, *layer1Derivs;

	void FeedForward();
	float Sigmoid(float x) const;
	float DerivSigmoid(float x) const;
	float ComputeCurrentLoss() const;

	void BackProp();
};

