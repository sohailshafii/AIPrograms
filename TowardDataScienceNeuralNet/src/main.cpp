//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#include "NeuralNetwork.h"

int main() {
	float x[4] = {0.0f, 0.0f, 1.0f, 1.0};
	float y[4] = {0.0f, 1.0f, 1.0f, 0.0};

	NeuralNetwork neuralNet(x, y, 4);
	neuralNet.configure(10500);

	return 0;
}
