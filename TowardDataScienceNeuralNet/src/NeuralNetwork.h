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

	void configure(int iterations);	

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

	// x would be 4x1, y would be 4x1
	// weights are four items each
	// TODO:
	// input
	// weights1 -- number of columns in inputx4
	// weights2 -- 4x1
	// output -- same shape as y
	// y
	//int input;
	//float 

	//def feedforward(self):
    //    self.layer1 = sigmoid(np.dot(self.input, self.weights1))
    //    self.output = sigmoid(np.dot(self.layer1, self.weights2))

    //def backprop(self):
    //    # application of the chain rule to find derivative of the loss function with respect to weights2 and weights1
    //    d_weights2 = np.dot(self.layer1.T, (2*(self.y - self.output) * sigmoid_derivative(self.output)))
    //    d_weights1 = np.dot(self.input.T,  (np.dot(2*(self.y - self.output) * sigmoid_derivative(self.output), self.weights2.T) * sigmoid_derivative(self.layer1)))

    //    # update the weights with the derivative (slope) of the loss function
    //    self.weights1 += d_weights1
    //    self.weights2 += d_weights2
};

