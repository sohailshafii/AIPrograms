// https://visualstudiomagazine.com/articles/2014/03/01/code-an-evolutionary-optimization-solution.aspx

#include <vector>
#include <iostream>
#include <iomanip>
#include "NeuralNetwork.h"
#include "Individual.h"

void ShowVector(double* vec, int numWeights, int valsPerRow,
	int decimals, bool newLine) {
	for (size_t i = 0; i < numWeights; i++) {
		if (i % valsPerRow)
		{
			std::cout << std::endl;
		}
		auto currElement = vec[i];
		if (currElement >= 0.0) {
			std::cout << " ";
		}
		std::cout << std::setprecision(decimals) <<
			currElement << " ";
	}
	if (newLine) {
		std::cout << std::endl;
	}
}

void ShowMatrix(double** matrix, int numRows,
	int numCols, int decimals, bool newLine) {
	for (int i = 0; i < numRows; i++) {
		std::cout << i << ": ";
		for (int j = 0; j < numCols; ++j) {
			auto currElement = matrix[i][j];
			if (matrix[i][j] >= 0.0) {
				std::cout << " ";
			}
			else {
				std::cout << "-";
			}
			std::cout << std::setprecision(decimals)
				<< currElement << " ";
		}
		std::cout << std::endl;
	}
	if (newLine) {
		std::cout << std::endl;
	}
}

int main() {
	srand((unsigned int)time(NULL));

	// Fisher's data set
	double** trainData = new double*[24];
	trainData[0] = new double[7] { 6.3, 2.9, 5.6, 1.8, 1, 0, 0 };
	trainData[1] = new double[7] { 6.9, 3.1, 4.9, 1.5, 0, 1, 0 };
	trainData[2] = new double[7] { 4.6, 3.4, 1.4, 0.3, 0, 0, 1 };
	trainData[3] = new double[7] { 7.2, 3.6, 6.1, 2.5, 1, 0, 0 };
	trainData[4] = new double[7] { 4.7, 3.2, 1.3, 0.2, 0, 0, 1 };
	trainData[5] = new double[7] { 4.9, 3, 1.4, 0.2, 0, 0, 1 };
	trainData[6] = new double[7] { 7.6, 3, 6.6, 2.1, 1, 0, 0 };
	trainData[7] = new double[7] { 4.9, 2.4, 3.3, 1, 0, 1, 0 };
	trainData[8] = new double[7] { 5.4, 3.9, 1.7, 0.4, 0, 0, 1 };
	trainData[9] = new double[7] { 4.9, 3.1, 1.5, 0.1, 0, 0, 1 };
	trainData[10] = new double[7] { 5, 3.6, 1.4, 0.2, 0, 0, 1 };
	trainData[11] = new double[7] { 6.4, 3.2, 4.5, 1.5, 0, 1, 0 };
	trainData[12] = new double[7] { 4.4, 2.9, 1.4, 0.2, 0, 0, 1 };
	trainData[13] = new double[7] { 5.8, 2.7, 5.1, 1.9, 1, 0, 0 };
	trainData[14] = new double[7] { 6.3, 3.3, 6, 2.5, 1, 0, 0 };
	trainData[15] = new double[7] { 5.2, 2.7, 3.9, 1.4, 0, 1, 0 };
	trainData[16] = new double[7] { 7, 3.2, 4.7, 1.4, 0, 1, 0 };
	trainData[17] = new double[7] { 6.5, 2.8, 4.6, 1.5, 0, 1, 0 };
	trainData[18] = new double[7] { 4.9, 2.5, 4.5, 1.7, 1, 0, 0 };
	trainData[19] = new double[7] { 5.7, 2.8, 4.5, 1.3, 0, 1, 0 };
	trainData[20] = new double[7] { 5, 3.4, 1.5, 0.2, 0, 0, 1 };
	trainData[21] = new double[7] { 6.5, 3, 5.8, 2.2, 1, 0, 0 };
	trainData[22] = new double[7] { 5.5, 2.3, 4, 1.3, 0, 1, 0 };
	trainData[23] = new double[7] { 6.7, 2.5, 5.8, 1.8, 1, 0, 0 };

	double** testData = new double*[6];
	testData[0] = new double[7] { 4.6, 3.1, 1.5, 0.2, 0, 0, 1 };
	testData[1] = new double[7] { 7.1, 3, 5.9, 2.1, 1, 0, 0 };
	testData[2] = new double[7] { 5.1, 3.5, 1.4, 0.2, 0, 0, 1 };
	testData[3] = new double[7] { 6.3, 3.3, 4.7, 1.6, 0, 1, 0 };
	testData[4] = new double[7] { 6.6, 2.9, 4.6, 1.3, 0, 1, 0 };
	testData[5] = new double[7] { 7.3, 2.9, 6.3, 1.8, 1, 0, 0 };

	std::cout << "Train data:\n";
	ShowMatrix(trainData, 24, 7, 1, true);

	std::cout << "Test data:\n";
	ShowMatrix(testData, 6, 7, 1, true);

	// 4-6-3 fully connected feed-forward neural network
	// four-inputs and three possible output classes.
	// six hidden nodes, which is arbitrary
	const int numInput = 4;
	const int numHidden = 6;
	const int numOutput = 3;
	NeuralNetwork neuralNet(numInput, numHidden, numOutput);

	// training parameters specific to EO
	int popSize = 8;
	int maxGeneration = 500;
	double exitError = 0.0;
	double mutateRate = 0.20;
	double mutateChange = 0.01;
	// selection pressure -- likelihood that the
	// two best individuals in the population will be
	// selected as parents for reprdouction
	double tau = 0.40;
	int numWeights;
	/*double* bestWeights = neuralNet.Train(trainData, popSize, maxGeneration,
		exitError, mutateRate, mutateChange, tau, numWeights);
	ShowVector(bestWeights, numWeights, 10, 3, true);

	// TODO: num weights
	/*neuralNet.SetWeights(bestWeights);
	double trainAcc = neuralNet.GetAccuracy(trainData);
	std::cout << "\nAccuracy of training data = "
		<< std::setprecision(4) << trainAcc;

	double testAcc = neuralNet.GetAccuracy(testData);
	std::cout << "\nAccuracy of test data = "
		<< std::setprecision(4) << testAcc;

	std::cout << "\nEnd Neural Net training demo.\n";

	for (int i = 0; i < 24; i++) {
		delete [] trainData[i];
	}
	delete [] trainData;

	for (int i = 0; i < 6; i++) {
		delete [] testData[i];
	}
	delete [] testData;*/

	return 0;
}

