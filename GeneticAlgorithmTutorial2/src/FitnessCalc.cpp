// http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#include "FitnessCalc.h"
#include "Individual.h"

unsigned int FitnessCalc::numChars = 64;
int* FitnessCalc::solution = new int[64];

void FitnessCalc::SetSolution(int* newSolution, int length) {
	if (solution != nullptr) {
		delete[] solution;
	}
	numChars = length;
	solution = new int[numChars];
	memcpy(solution, newSolution, length * sizeof(int));
}

void FitnessCalc::SetSolution(std::string const & newSolution) {
	if (solution != nullptr) {
		delete[] solution;
	}
	numChars = (unsigned int)newSolution.size();
	solution = new int[numChars];
	const char* charVersion = newSolution.c_str();

	// Loop through each character of our string and save it in our byte 
	// array
	for (unsigned int i = 0; i < numChars; i++) {
		solution[i] = (charVersion[i] == '1') ? 1 : 0;
	}
}

int FitnessCalc::GetFitness(Individual const & individual) {
	unsigned int fitness = 0;
	unsigned int individualSize = individual.Size();

	// Loop through our individuals genes and compare them to our cadidates
	for (unsigned int i = 0; i < individualSize && i < numChars; i++) {
		if (individual.GetGene(i) == solution[i]) {
			fitness++;
		}
	}
	return fitness;
}

int FitnessCalc::GetMaxFitness() {
	return numChars;
}