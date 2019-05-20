// Sohail Shafii
// from:
// https://blog.sicara.com/getting-started-genetic-algorithms-python-tutorial-81ffa1dd72f9

#include "PopulationData.h"

int main() {
	std::string testPassword = "hello";

	int populationSize = 100;
	int numBestSamples = 20;
	int numLuckyFewIndices = 20;
	int numberOfChildren = 5;

	PopulationData firstPopulation = PopulationData(populationSize,
		numLuckyFewIndices+numBestSamples, numberOfChildren, testPassword.size());

	firstPopulation.testInitialData();
	firstPopulation.testFitnessFunction(testPassword, "hel33");
	firstPopulation.measurePerfAndTestSort(testPassword);

	return 0;
}
