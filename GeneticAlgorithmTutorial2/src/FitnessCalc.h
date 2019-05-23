// http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#pragma once

#include <string>

class Individual;

class FitnessCalc {
public:
	static int numChars;
	static int* solution;

	static void setSolution(int* newSolution, int length);
	static void setSolution(const std::string& newSolution);

    static int getFitness(const Individual& individual);
    static int getMaxFitness();
};
