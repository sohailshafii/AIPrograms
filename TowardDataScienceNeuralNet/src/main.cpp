//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#include "NeuralNetwork.h"

int main() {
	// input format:
	// 0 0 1   
    // 0 1 1   
    // 1 0 1    
    // 1 1 1 
    float **x = new float*[4];
    for (int i = 0; i < 4; i++) {
    	x[i] = new float[3];
    }
    x[0][0] = 0.0f; x[0][1] = 0.0f; x[0][2] = 1.0f;
    x[1][0] = 0.0f; x[1][1] = 1.0f; x[1][2] = 1.0f;
    x[2][0] = 1.0f; x[2][1] = 0.0f; x[2][2] = 1.0f;
    x[3][0] = 1.0f; x[3][1] = 1.0f; x[3][2] = 1.0f;

	float y[4] = {0.0f, 1.0f, 1.0f, 0.0};

	NeuralNetwork neuralNet(x, y, 4, 3);
	neuralNet.configure(10500);

	for(int i = 0; i < 4; i++) {
		delete [] x[i];
	}
	delete [] x;

	return 0;
}
