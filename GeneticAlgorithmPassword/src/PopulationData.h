// Sohail Shafii
// from:
// https://blog.sicara.com/getting-started-genetic-algorithms-python-tutorial-81ffa1dd72f9

#pragma once

#include <string>
#include <random>

class PopulationData {
public:
	struct MemberData {
		std::string word;
		float performance;
	};

	PopulationData() :currentGeneration(nullptr),
		breeders(nullptr), nextGeneration(nullptr) {

	}

	PopulationData(unsigned int popSize, unsigned  int numBreeders,
		unsigned int numberOfChildren, unsigned  int passwordLength);
	PopulationData(const PopulationData& prevPopData,
		unsigned int popSize, unsigned  int numBreeders,
		unsigned int numberOfChildren);
	PopulationData(const PopulationData &p2);

	PopulationData& operator=(const PopulationData& other);

	~PopulationData();

	void makeRandomPopulation(unsigned int passwordLength);

	void makeNextGeneration(const std::string &password,
		unsigned int numBestSamples, unsigned int numLuckyFewIndices,
		float chanceOfMutation);

	void calculatePerf(const std::string& password);
	void printPopulation() const;

	void testInitialData() const;
	void testFitnessFunction(const std::string&
		testPassword, const std::string& halfFitnessVersion) const;
	void measurePerfAndTestSort(const std::string&
		testPassword);

private:
	std::string generateAWord(unsigned int length);

	void computePerfPopulation(const std::string& password);
	float fitnessFunction(const std::string& password,
		const std::string& testWord) const;

	void selectBreedersFromPopulation(
		unsigned int numBestSamples, unsigned int numLuckyFewIndices);
	std::string createChild(const std::string& individual1,
		const std::string& individual2);
	void createChildren();

	std::string mutateWord(const std::string& word);
	void mutateNextPopulation(
		float chanceOfMutation);

	void allocateAndCopyFrom(const PopulationData& other);
	void copyFrom(const PopulationData& other);
	//static void allocateRandData();

	static float randUnitVal();
	static char randomLetterAscii();

	MemberData* currentGeneration;
	MemberData* breeders;
	MemberData* nextGeneration;

	unsigned int populationSize;
	unsigned int numBreeders;
	unsigned int numberOfChildren;

	//static std::mt19937 *gen; 
	//static std::uniform_real_distribution<> *dis;
};
