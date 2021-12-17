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

	PopulationData(unsigned int popSize, unsigned int numBestBreeders,
		unsigned int numLuckyBreeders, unsigned int numberOfChildren,
		unsigned  int passwordLength);
	PopulationData(const PopulationData& prevPopData,
		unsigned int popSize, unsigned  int numBestBreeders,
		unsigned int numLuckyBreeders, unsigned int numberOfChildren);
	PopulationData(const PopulationData &p2);

	PopulationData& operator=(const PopulationData& other);

	~PopulationData();

	void MakeRandomPopulation(unsigned int passwordLength);

	void MakeNextGeneration(const std::string &password,
		float chanceOfMutation);

	void CalculatePerf(const std::string& password);
	void printPopulation() const;

	void TestInitialData() const;
	void TestFitnessFunction(const std::string&
		testPassword, const std::string& halfFitnessVersion) const;
	void MeasurePerfAndTestSort(const std::string&
		testPassword);

private:
	std::string GenerateAWord(unsigned int length);

	void ComputePerfPopulation(const std::string& password);
	float FitnessFunction(const std::string& password,
		const std::string& testWord) const;

	void SelectBreedersFromPopulation();
	std::string CreateChild(const std::string& individual1,
		const std::string& individual2);
	void CreateChildren();

	std::string MutateWord(const std::string& word);
	void MutateNextPopulation(float chanceOfMutation);

	void AllocateAndCopyFrom(const PopulationData& other);
	void CopyFrom(const PopulationData& other);
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
