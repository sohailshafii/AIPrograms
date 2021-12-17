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

	PopulationData firstPopulation = PopulationData(populationSize, numBestSamples,
		numLuckyFewIndices, numberOfChildren, (unsigned int)testPassword.size());

	firstPopulation.TestInitialData();
	firstPopulation.TestFitnessFunction(testPassword, "hel33");
	firstPopulation.MeasurePerfAndTestSort(testPassword);

	return 0;
}
