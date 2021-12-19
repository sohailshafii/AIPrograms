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

	PopulationData() : currentGeneration(nullptr),
		breeders(nullptr), nextGeneration(nullptr) {
	}

	PopulationData(unsigned int popSize, unsigned int numBestBreeders,
		unsigned int numLuckyBreeders, unsigned int numberOfChildren,
		unsigned  int passwordLength);
	PopulationData(PopulationData const & prevPopData,
		unsigned int popSize, unsigned  int numBestBreeders,
		unsigned int numLuckyBreeders, unsigned int numberOfChildren);
	PopulationData(PopulationData const & p2);

	PopulationData& operator=(PopulationData const & other);

	~PopulationData();

	void MakeRandomPopulation(unsigned int passwordLength);

	void MakeNextGeneration(std::string const & password,
		float chanceOfMutation);

	void CalculatePerf(std::string const & password);
	void printPopulation() const;

	void TestInitialData() const;
	void TestFitnessFunction(std::string const & testPassword,
		std::string const & halfFitnessVersion) const;
	void MeasurePerfAndTestSort(std::string const & testPassword);

private:
	std::string GenerateAWord(unsigned int length);

	void ComputePerfPopulation(std::string const & password);
	float FitnessFunction(std::string const & password,
		std::string const & testWord) const;

	void SelectBreedersFromPopulation();
	std::string CreateChild(std::string const & individual1,
		std::string const & individual2);
	void CreateChildren();

	std::string MutateWord(std::string const & word);
	void MutateNextPopulation(float chanceOfMutation);

	void AllocateAndCopyFrom(PopulationData const & other);
	void CopyFrom(PopulationData const & other);
	//static void allocateRandData();

	static float RandUnitVal();
	static char RandomLetterAscii();

	MemberData* currentGeneration;
	MemberData* breeders;
	MemberData* nextGeneration;

	unsigned int populationSize;
	unsigned int numBestBreeders, numLuckyBreeders;
	unsigned int numberOfChildren;

	//static std::mt19937 *gen; 
	//static std::uniform_real_distribution<> *dis;
};
