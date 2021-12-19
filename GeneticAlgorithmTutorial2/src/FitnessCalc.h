// http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#pragma once

#include <string>

class Individual;

class FitnessCalc {
public:
	static unsigned int numChars;
	static int* solution;

	static void SetSolution(int* newSolution, int length);
	static void SetSolution(std::string const & newSolution);

	static int GetFitness(Individual const & individual);
	static int GetMaxFitness();
};
