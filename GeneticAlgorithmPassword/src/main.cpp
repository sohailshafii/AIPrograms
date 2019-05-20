// from:
// https://blog.sicara.com/getting-started-genetic-algorithms-python-tutorial-81ffa1dd72f9

#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cassert>
#include <random>

#include "PopulationData.h"

float fitnessFunction(const std::string& password,
	const std::string& testWord);
std::string createChild(const std::string& individual1,
	const std::string& individual2);
std::string mutateWord(const std::string& word);

std::vector<PopulationData> evolveMultipleTimes(int numberOfGenerations,
	std::string& password, int populationSize, int numBestSamples, int numLuckyFewIndices,
	int numChildren, float chanceOfMutation) {
	std::vector<PopulationData> allGenerations;

	PopulationData firstPopulation = PopulationData(populationSize,
		numLuckyFewIndices+numBestSamples, numChildren, password.size());
	allGenerations.push_back(firstPopulation);

	for (int i = 0; i < numberOfGenerations; i++) {
		std::cout << "Evolving generation " << i << "...\n";
		auto& currGeneration = allGenerations[i];
		currGeneration.makeNextGeneration(password, 
			numBestSamples, numLuckyFewIndices, chanceOfMutation);
		PopulationData nextGen = PopulationData(
			currGeneration, populationSize,
			numLuckyFewIndices+numBestSamples, numChildren);
		allGenerations.push_back(nextGen);
		std::cout << "Evolved generation " << i << ".\n";
	}

	return allGenerations;
}

/*void runTests() {
	std::string testPassword = "hello";

	std::cout << "Running tests...\n";

	float perfectFitness = fitnessFunction(testPassword, "hello");
	float halfFitness = fitnessFunction(testPassword, "h30lo");
	float badFitness = fitnessFunction(testPassword, "test");

	std::cout << "Perfect fitness: " << perfectFitness << ", "
		<< "half fitness: " << halfFitness << ", bad fitness: "
		<< badFitness << ".\n";

	assert(perfectFitness == 100.0f);
	assert(halfFitness > 50.0f && halfFitness < 100.0f);
	assert(badFitness < 0.0f);
}*/

int main() {
	srand(time(NULL));

	//runTests();
	//return 0;

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
	if ( ((numBestSamples + numLuckyFewIndices)*0.5f*numberOfChildren)
		!= populationSize) {
		std::cerr << "Population size not stable!\n";
	}
	else {
		std::vector<PopulationData> allEvolutions =
			evolveMultipleTimes(numberOfGenerations, password, populationSize, 
				numBestSamples, numLuckyFewIndices, numberOfChildren, chanceOfMutation);
		std::cout << "Performance of last generation:\n";
		auto& lastGen = allEvolutions[allEvolutions.size()-1];
		lastGen.calculatePerf(password);
		lastGen.printPopulation();
	}
	return 0;
}
