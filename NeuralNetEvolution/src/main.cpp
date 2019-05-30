#include <vector>
#include <iostream>
#include <iomanip>

void ShowVector(std::vector<double> vec, int valsPerRow,
	int decimals, bool newLine) {
	int numElements = vec.size();
	for (int i = 0; i < numElements; i++) {
		if (i % valsPerRow) std::cout << std::endl;
		auto currElement = vec[i];
		if (currElement >= 0.0) {
			std::cout << " ";
		}
		std::cout << std::setprecision(decimals) <<
			decimals << " ";
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
			if (matrix[i][j] >= 0.0) {
				std::cout << " ";
			}
			else {
				std::cout << "-";
			}
			std::cout << std::setprecision(decimals)
				<< decimals << " ";
		}
		std::cout << std::endl;
	}
	if (newLine) {
		std::cout << std::endl;
	}
}

class NeuralNetwork {

};

int main() {

	return 0;
}

