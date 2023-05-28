// Sohail Shafii
// from:
// https://blog.sicara.com/getting-started-genetic-algorithms-python-tutorial-81ffa1dd72f9

#include "PopulationData.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <chrono>

//std::mt19937 *PopulationData::gen; 
//std::uniform_real_distribution<> *PopulationData::dis;

PopulationData::PopulationData(unsigned int popSize,
	unsigned int numBestBreeders, unsigned int numLuckyBreeders,
	unsigned int numberOfChildren, unsigned int passwordLength) {
	//PopulationData::allocateRandData();

	populationSize = popSize;
	this->numBestBreeders = numBestBreeders;
	this->numLuckyBreeders = numLuckyBreeders;
	this->numberOfChildren = numberOfChildren;

	currentGeneration = new MemberData[popSize];
	// make random generation since no previous one was provided
	MakeRandomPopulation(passwordLength);
	breeders = new MemberData[numBestBreeders + numLuckyBreeders];
	nextGeneration = new MemberData[populationSize];
}

PopulationData::PopulationData(PopulationData const & prevPopData,
	unsigned int popSize, unsigned int numBestBreeders,
	unsigned int numLuckyBreeders, unsigned int numberOfChildren) {
	//allocateRandData();

	populationSize = popSize;
	this->numBestBreeders = numBestBreeders;
	this->numLuckyBreeders = numLuckyBreeders;
	this->numberOfChildren = numberOfChildren;

	currentGeneration = new MemberData[popSize];
	for (unsigned int i = 0; i < popSize; i++) {
		currentGeneration[i] = prevPopData.nextGeneration[i];
	}
	breeders = new MemberData[numBestBreeders + numLuckyBreeders];
	nextGeneration = new MemberData[populationSize];
}

PopulationData::PopulationData(PopulationData const & p2) {
	AllocateAndCopyFrom(p2);
	//allocateRandData();
}

PopulationData::~PopulationData() {
	if (currentGeneration != nullptr) {
		delete[] currentGeneration;
	}
	if (breeders != nullptr) {
		delete[] breeders;
	}
	if (nextGeneration != nullptr) {
		delete[] nextGeneration;
	}
}

PopulationData& PopulationData::operator=(PopulationData const & other)
{
	if (this != &other) {
		if (this->populationSize != other.populationSize ||
			this->numBestBreeders != other.numBestBreeders ||
			this->numLuckyBreeders != other.numLuckyBreeders ||
			this->numberOfChildren != other.numberOfChildren) {
			if (currentGeneration != nullptr) {
				delete[] currentGeneration;
			}
			if (breeders != nullptr) {
				delete[] breeders;
			}
			if (nextGeneration != nullptr) {
				delete[] nextGeneration;
			}
			AllocateAndCopyFrom(other);
		}
		else {
			CopyFrom(other);
		}
	}
	return *this;
}

void PopulationData::AllocateAndCopyFrom(PopulationData const & other) {
	this->populationSize = other.populationSize;
	this->numBestBreeders = other.numBestBreeders;
	this->numLuckyBreeders = other.numLuckyBreeders;
	this->numberOfChildren = other.numberOfChildren;

	this->currentGeneration = new MemberData[populationSize];
	this->breeders = new MemberData[numBestBreeders + numLuckyBreeders];
	this->nextGeneration = new MemberData[populationSize];
	CopyFrom(other);
}

void PopulationData::CopyFrom(PopulationData const & other) {
	for (unsigned int i = 0; i < populationSize; i++) {
		this->currentGeneration[i] =
			other.currentGeneration[i];
	}
	for (unsigned int i = 0; i < numBestBreeders + numLuckyBreeders; i++) {
		this->breeders[i] = other.breeders[i];
	}
	for (unsigned int i = 0; i < populationSize; i++) {
		this->nextGeneration[i] = other.nextGeneration[i];
	}
}

/*void PopulationData::AllocateRandData() {
	if (gen != nullptr) {
		return;
	}
	// Will be used to obtain a seed for the random number engine
	std::random_device rd;
	// Standard mersenne_twister_engine seeded with rd()
	gen = new std::mt19937(rd());
	dis = new std::uniform_real_distribution<>(0.0f, 1.0f);
}*/

void PopulationData::MakeRandomPopulation(unsigned int passwordLength) {
	for (unsigned int i = 0; i < populationSize; i++) {
		currentGeneration[i].word = GenerateAWord(passwordLength);
	}
}

void PopulationData::MakeNextGeneration(std::string const & password,
	float chanceOfMutation) {
	ComputePerfPopulation(password);
	SelectBreedersFromPopulation();
	CreateChildren();
	MutateNextPopulation(chanceOfMutation);
}

void PopulationData::CalculatePerf(std::string const & password) {
	ComputePerfPopulation(password);
}

void PopulationData::PrintPopulation() const {
	std::cout << "Printing current generation...\n";
	for (unsigned int i = 0; i < populationSize; i++) {
		auto& individual = currentGeneration[i];
		std::cout << "Word " << i << " is: " << individual.word
			<< ", performance: " << individual.performance << ".\n";
	}
}

std::string PopulationData::GenerateAWord(unsigned int length) {
	std::string generatedWord = "";
	for (unsigned int i = 0; i < length; i++) {
		generatedWord += RandomLetterAscii();
	}

	return generatedWord;
}

void PopulationData::ComputePerfPopulation(std::string const & password) {
	for (unsigned int i = 0; i < populationSize; i++) {
		auto& individual = currentGeneration[i];
		individual.performance = FitnessFunction(password,
			individual.word);
	}
	std::sort(currentGeneration,
		currentGeneration + populationSize,
		[](const MemberData& a, const MemberData& b) {
		return a.performance > b.performance;
	});
}

float PopulationData::FitnessFunction(std::string const & password,
	std::string const & testWord) const {
	if (password.size() != testWord.size()) {
		std::cout << "Word and password incompatible!\n";
		return -1.0f;
	}
	else {
		int score = 0;
		size_t numCharacters = password.size();
		for (size_t i = 0; i < numCharacters; i++) {
			if (password[i] == testWord[i]) {
				score++;
			}
		}
		return (float)score * 100.0f / (float)numCharacters;
	}
}

void PopulationData::SelectBreedersFromPopulation() {
	int pickedIndex = 0;
	// pick from the front as those are the best
	// it is expected that the current generation is sorted
	// before this point
	for (unsigned int i = 0; i < numBestBreeders; i++) {
		breeders[pickedIndex] = currentGeneration[pickedIndex];
		pickedIndex++;
	}

	for (unsigned int i = 0; i < numLuckyBreeders; i++) {
		int newRandomIndex;
		bool duplicateFound = true;
		// make sure lucky index doesn't overlap with best ones
		while (duplicateFound) {
			newRandomIndex = rand() % populationSize;
			duplicateFound = false;
			for (int j = 0; j < pickedIndex; j++) {
				if (&breeders[pickedIndex] == &breeders[newRandomIndex]) {
					duplicateFound = true;
					break;
				}
			}
		}
		breeders[pickedIndex] = currentGeneration[newRandomIndex];
		pickedIndex++;
	}

	auto seed =
		(unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(breeders, breeders + numBestBreeders + numLuckyBreeders,
		std::default_random_engine(seed));
}

std::string PopulationData::CreateChild(std::string const & individual1,
	std::string const & individual2) {
	std::string child = "";
	auto numCharacters = individual1.size();
	for (size_t i = 0; i < numCharacters; i++) {
		child += ((rand() % 100) < 50) ?
			individual1[i] : individual2[i];
	}
	return child;
}

void PopulationData::CreateChildren() {
	unsigned int numTotalBreeders = numBestBreeders + numLuckyBreeders;
	auto numHalfPop = numTotalBreeders / 2;
	auto childIndex = 0;
	for (unsigned int i = 0; i < numHalfPop; i++) {
		for (unsigned int j = 0; j < numberOfChildren; j++) {
			auto nextChild = CreateChild(breeders[i].word,
				breeders[numTotalBreeders - 1 - i].word);
			nextGeneration[childIndex].word = nextChild;
			childIndex++;
		}
	}
}

std::string PopulationData::MutateWord(std::string const & word) {
	size_t wordLength = word.size();
	auto randVal = rand();
	size_t test = randVal % wordLength;

	size_t indexModification = (size_t)(rand() % wordLength);
	std::string modifiedWord;

	if (indexModification == 0) {
		modifiedWord += PopulationData::RandomLetterAscii();
		modifiedWord += word.substr(1);
	}
	else {
		modifiedWord += word.substr(0, indexModification);
		modifiedWord += PopulationData::RandomLetterAscii();
		modifiedWord += word.substr(indexModification + 1);
	}
	return modifiedWord;
}

void PopulationData::MutateNextPopulation(
	float chanceOfMutation) {
	for (unsigned int i = 0; i < populationSize; i++) {
		int randValue = rand();
		float chance = PopulationData::RandUnitVal();
		chance *= 100.0f;
		if (chance < chanceOfMutation) {
			nextGeneration[i].word = MutateWord(
				nextGeneration[i].word);
		}
	}
}

void PopulationData::TestInitialData() const {
	assert(currentGeneration != nullptr);
	assert(breeders != nullptr);
	assert(nextGeneration != nullptr);

	assert(populationSize != 0);
	assert(numBestBreeders != 0);
	assert(numLuckyBreeders != 0);
	assert(numberOfChildren != 0);

	assert(((numBestBreeders + numLuckyBreeders) * numberOfChildren / 2)
		== populationSize);

	//assert(PopulationData::gen != nullptr); 
	//assert(PopulationData::dis != nullptr);
}

void PopulationData::TestFitnessFunction(std::string const & testPassword,
	std::string const & halfFitnessVersion) const {
	float perfectFitness = FitnessFunction(testPassword, testPassword);
	float halfFitness = FitnessFunction(testPassword, halfFitnessVersion);
	float badFitness = FitnessFunction(testPassword, "test");

	std::cout << "Perfect fitness: " << perfectFitness << ", "
		<< "half fitness: " << halfFitness << ", bad fitness: "
		<< badFitness << ".\n";

	assert(perfectFitness == 100.0f);
	assert(halfFitness > 50.0f && halfFitness < 100.0f);
	assert(badFitness < 0.0f);
}

void PopulationData::MeasurePerfAndTestSort(std::string const & testPassword) {
	ComputePerfPopulation(testPassword);

	bool properOrder = true;
	for (unsigned int i = 1; i < populationSize - 1; i++) {
		auto& curr = currentGeneration[i],
			prev = currentGeneration[i - 1];
		if (prev.performance < curr.performance) {
			properOrder = false;
			break;
		}
	}

	assert(properOrder);
}

float PopulationData::RandUnitVal() {
	//return (float)(*dis)(*gen);
	return (float)rand() / (float)RAND_MAX;
}

char PopulationData::RandomLetterAscii() {
	float unitVal = PopulationData::RandUnitVal();
	return (char)(97 + (int)(26.0f*unitVal));
}

