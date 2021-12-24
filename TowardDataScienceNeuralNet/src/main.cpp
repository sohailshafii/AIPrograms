//https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

#include "NeuralNetwork.h"
#include "Matrix.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

void RunMatrixTests() {
	Matrix m1(2, 3), m2(3, 2);

	m1(0, 0) = 1.0f; m1(0, 1) = 2.0f; m1(0, 2) = 0.0f;
	m1(1, 0) = 5.0f; m1(1, 1) = 6.0f; m1(1, 2) = 2.0f;

	m2(0, 0) = 1.0f; m2(0, 1) = -2.0f;
	m2(1, 0) = 8.0f; m2(1, 1) = 3.0f;
	m2(2, 0) = 9.0f; m2(2, 1) = 6.0f;

	Matrix product = m1*m2;
	if (product(0, 0) != 17.0f || product(0, 1) != 4.0f ||
		product(1, 0) != 71.0f || product(1, 1) != 20.0f) {
		std::cout << "Matrix multiplication doesn't work! Result\n";
		int numRows = product.GetNumRows();
		int numCols = product.GetNumColumns();
		for (int row = 0; row < numRows; row++) {
			for (int column = 0; column < numCols;
				column++) {
				std::cout << product(row, column) << ", ";
			}
			std::cout << std::endl;
		}
	}
}

int main() {
	srand((unsigned int)time(NULL));

	RunMatrixTests();

	// input format:
	// 0 0 1   
	// 0 1 1   
	// 1 0 1    
	// 1 1 1 

	Matrix x(4, 3);
	x[0][0] = 0.0f; x[0][1] = 0.0f; x[0][2] = 1.0f;
	x[1][0] = 0.0f; x[1][1] = 1.0f; x[1][2] = 1.0f;
	x[2][0] = 1.0f; x[2][1] = 0.0f; x[2][2] = 1.0f;
	x[3][0] = 1.0f; x[3][1] = 1.0f; x[3][2] = 1.0f;

	Matrix y(4, 1);
	y[0][0] = 0.0f;
	y[1][0] = 1.0f;
	y[2][0] = 1.0f;
	y[3][0] = 0.0f;

	NeuralNetwork neuralNet(x, y);
	neuralNet.Configure(20000);

	return 0;
}
