#pragma once

#include <string>
#include <random>

class PopulationData {
public:
	struct MemberData {
		std::string word;
		float performance;
	};

	PopulationData(int popSize, int numBreeders,
		int numberOfChildren, int passwordLength);
	PopulationData(const PopulationData& prevPopData,
		int popSize, int numBreeders, int numberOfChildren);
	PopulationData(const PopulationData &p2);

	PopulationData& operator=(const PopulationData& other);

	~PopulationData();

	void makeRandomPopulation(int passwordLength);

	void makeNextGeneration(const std::string &password,
		int numBestSamples, int numLuckyFewIndices,
		float chanceOfMutation);

	void calculatePerf(const std::string& password);
	void printPopulation() const;

	void testInitialData() const;
	void testFitnessFunction(const std::string&
		testPassword, const std::string& halfFitnessVersion) const;
	void measurePerfAndTestSort(const std::string&
		testPassword);

private:
	std::string generateAWord(int length);

	void computePerfPopulation(const std::string& password);
	float fitnessFunction(const std::string& password,
		const std::string& testWord) const;

	void selectBreedersFromPopulation(
		int numBestSamples, int numLuckyFewIndices);
	std::string createChild(const std::string& individual1,
		const std::string& individual2);
	void createChildren();

	std::string mutateWord(const std::string& word);
	void mutateNextPopulation(
		float chanceOfMutation);

	void AllocateAndCopyFrom(const PopulationData& other);
	static void AllocateRandData();

	static float randUnitVal();
	static char randomLetterAscii();

	MemberData* currentGeneration;
	MemberData* breeders;
	MemberData* nextGeneration;

	int populationSize;
	int numBreeders;
	int numberOfChildren;

    static std::mt19937 *gen; 
    static std::uniform_real_distribution<> *dis;
};
