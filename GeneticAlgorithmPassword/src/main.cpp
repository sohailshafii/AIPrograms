// Sohail Shafii
// from:
// https://blog.sicara.com/getting-started-genetic-algorithms-python-tutorial-81ffa1dd72f9

#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cassert>
#include <random>

#include "PopulationData.h"

std::vector<PopulationData> evolveMultipleTimes(int numberOfGenerations,
	std::string& password, int populationSize, int numBestSamples, int numLuckyFewIndices,
	int numChildren, float chanceOfMutation) {
	std::vector<PopulationData> allGenerations;

	PopulationData firstPopulation = PopulationData(populationSize,
		numLuckyFewIndices + numBestSamples, numChildren, (unsigned int)password.size());
	allGenerations.push_back(firstPopulation);

	for (int i = 0; i < numberOfGenerations; i++) {
		std::cout << "Evolving generation " << i << "...\n";
		auto& currGeneration = allGenerations[i];
		currGeneration.makeNextGeneration(password,
			numBestSamples, numLuckyFewIndices, chanceOfMutation);
		PopulationData nextGen = PopulationData(
			currGeneration, populationSize,
			numLuckyFewIndices + numBestSamples, numChildren);
		allGenerations.push_back(nextGen);
		std::cout << "Evolved generation " << i << ".\n";
	}

	return allGenerations;
}

int main() {
	srand(time(NULL));

	std::string password = "banana";
	int populationSize = 100;
	int numBestSamples = 20;
	int numLuckyFewIndices = 20;

	int numberOfChildren = 5;
	int numberOfGenerations = 50;
	float chanceOfMutation = 5.0f;

	// we select (bestSample + luckyFew) to breed the next generation
	// we take a pair from each half of that generation to create a child,
	// so the next generation's children needs to match the population size
	if (((numBestSamples + numLuckyFewIndices)*0.5f*numberOfChildren)
		!= populationSize) {
		std::cerr << "Population size not stable!\n";
	}
	else {
		std::vector<PopulationData> allEvolutions =
			evolveMultipleTimes(numberOfGenerations, password, populationSize,
				numBestSamples, numLuckyFewIndices, numberOfChildren, chanceOfMutation);

		std::cout << "Performance of first generation:\n";
		auto& firstGen = allEvolutions[0];
		firstGen.printPopulation();

		std::cout << "Performance of last generation:\n";
		auto& lastGen = allEvolutions[allEvolutions.size() - 1];
		lastGen.calculatePerf(password);
		lastGen.printPopulation();
	}
	return 0;
}
