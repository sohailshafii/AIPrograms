#include "PopulationData.h"

#include <iostream>
#include <cassert>

std::mt19937 *PopulationData::gen; 
std::uniform_real_distribution<> *PopulationData::dis;

PopulationData::PopulationData(int popSize, int numBreeders,
	int numberOfChildren, int passwordLength) {
	PopulationData::AllocateRandData();

	populationSize = popSize;
	this->numBreeders = numBreeders;
	this->numberOfChildren = numberOfChildren;

	currentGeneration = new MemberData[popSize];
	// make random generation since no previous one was provided
	makeRandomPopulation(passwordLength);
	breeders = new MemberData[numBreeders];
	nextGeneration = new MemberData[populationSize];
}

PopulationData::PopulationData(const PopulationData& prevPopData,
	int popSize, int numBreeders, int numberOfChildren) {
	AllocateRandData();

	populationSize = popSize;
	this->numBreeders = numBreeders;
	this->numberOfChildren = numberOfChildren;

	currentGeneration = new MemberData[popSize];
	for (int i = 0; i < popSize; i++) {
		currentGeneration[i] = prevPopData.nextGeneration[i];
	}
	breeders = new MemberData[numBreeders];
	nextGeneration = new MemberData[populationSize];
}

PopulationData::PopulationData(const PopulationData &p2) {
	AllocateAndCopyFrom(p2);
	AllocateRandData();
}

PopulationData::~PopulationData() { 
	if (currentGeneration != nullptr) {
		delete [] currentGeneration;
	}
	if (breeders != nullptr) {
		delete [] breeders;
	}
	if (nextGeneration != nullptr) {
		delete [] nextGeneration;
	}
}

PopulationData& PopulationData::operator=(const PopulationData& other)
{
	if (this != &other) {
		AllocateAndCopyFrom(other);
	}
	return *this;
}		

void PopulationData::AllocateAndCopyFrom(const PopulationData& other) {
	this->populationSize = other.populationSize;
	this->numBreeders = other.numBreeders;
	this->numberOfChildren = other.numberOfChildren;

	this->currentGeneration = new MemberData[populationSize];
	for (int i = 0; i < populationSize; i++) {
		this->currentGeneration[i] =
			other.currentGeneration[i];
	}
	this->breeders = new MemberData[numBreeders];
	for (int i = 0; i < numBreeders; i++) {
		this->breeders[i] = other.breeders[i];
	}
	this->nextGeneration = new MemberData[populationSize];
	for (int i = 0; i < populationSize; i++) {
		this->nextGeneration[i] = other.nextGeneration[i];
	}
}

void PopulationData::AllocateRandData() {
	if (gen != nullptr) {
		return;
	}
	//Will be used to obtain a seed for the random number engine
	std::random_device rd;  
	//Standard mersenne_twister_engine seeded with rd()
	gen = new std::mt19937(rd());
	dis = new std::uniform_real_distribution<>(0.0f, 1.0f);
}

void PopulationData::makeRandomPopulation(int passwordLength) {
	for (int i = 0; i < populationSize; i++) {
		currentGeneration[i].word = generateAWord(passwordLength);
	}
}

void PopulationData::makeNextGeneration(const std::string &password,
	int numBestSamples, int numLuckyFewIndices,
	float chanceOfMutation) {
	computePerfPopulation(password);
	selectBreedersFromPopulation(numBestSamples, numLuckyFewIndices);
	createChildren();
	mutateNextPopulation(chanceOfMutation);
}

void PopulationData::calculatePerf(const std::string& password) {
	computePerfPopulation(password);
}

void PopulationData::printPopulation() const {
	std::cout << "Printing current generation...\n";
	for (int i = 0; i < populationSize; i++) {
		auto& individual = currentGeneration[i];
		std::cout << "Word " << i << " is: " << individual.word
			<< ", performance: " << individual.performance << ".\n";
	}
}

std::string PopulationData::generateAWord(int length) {
	std::string generatedWord = "";
	for(int i = 0; i < length; i++) {
		generatedWord += randomLetterAscii();
	}

	return generatedWord;
}

void PopulationData::computePerfPopulation(const std::string& password) {
	for(int i = 0; i < populationSize; i++) {
		auto& individual = currentGeneration[i];
		individual.performance = fitnessFunction(password,
			individual.word);
	}
	std::sort(currentGeneration,
		currentGeneration+populationSize, 
		[](const MemberData& a, const MemberData& b) {
		return a.performance > b.performance;
	});
}

float PopulationData::fitnessFunction(const std::string& password,
	const std::string& testWord) const {
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
		return (float)score * 100.0f/(float)numCharacters;
	}
}

void PopulationData::selectBreedersFromPopulation(
	int numBestSamples, int numLuckyFewIndices) {
	
	int pickedIndex = 0;
	// pick from the front as those are the best
	for (int i = 0; i < numBestSamples; i++) {
		breeders[pickedIndex] = currentGeneration[pickedIndex];
		pickedIndex++;
	}

	for (int i = 0; i < numLuckyFewIndices; i++) {
		breeders[pickedIndex] = currentGeneration[rand()
				% populationSize];
		pickedIndex++;
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	std::shuffle (breeders, breeders + numBreeders,
  		std::default_random_engine(seed));
}

std::string PopulationData::createChild(const std::string& individual1,
	const std::string& individual2) {
	std::string child = "";
	int numCharacters = individual1.size();
	for (int i = 0; i < numCharacters; i++) {
		child +=  ((rand() % 100) < 50) ?
			individual1[i] : individual2[i];
	}
	return child;
}

void PopulationData::createChildren() {
	int numHalfPop = numBreeders/2;
	int childIndex = 0;
	for (int i = 0; i < numHalfPop; i++) {
		for (int j = 0; j < numberOfChildren; j++) {
			auto nextChild = createChild(breeders[i].word,
				breeders[numBreeders - 1 - i].word);
			nextGeneration[childIndex].word = nextChild;
			childIndex++;
		}
	}
}

std::string PopulationData::mutateWord(const std::string& word) {
	size_t wordLength = word.size();
	auto randVal = rand();
	size_t test = randVal % wordLength;

	size_t indexModification = (size_t)(rand() % wordLength);
	std::string modifiedWord;

	if (indexModification == 0) {
		modifiedWord += PopulationData::randomLetterAscii();
		modifiedWord += word.substr(1);
	}
	else {
		modifiedWord += word.substr(0, indexModification);
		modifiedWord += PopulationData::randomLetterAscii();
		modifiedWord += word.substr(indexModification+1);
	}
	return modifiedWord;
}

void PopulationData::mutateNextPopulation(
	float chanceOfMutation) {
	for (int i = 0; i < populationSize; i++) {
		// TODO: best way to generate between 0-1?
		int randValue = rand();
		float chance = PopulationData::randUnitVal();
		chance *= 100.0f;
		if (chance < chanceOfMutation) {
			nextGeneration[i].word = mutateWord(
				nextGeneration[i].word);
		}
	}
}

void PopulationData::testInitialData() const {
	assert(currentGeneration != nullptr);
	assert(breeders != nullptr);
	assert(nextGeneration != nullptr);

	assert(populationSize != 0);
	assert(numBreeders != 0);
	assert(numberOfChildren != 0);

	assert((numBreeders*numberOfChildren/2)
		== populationSize);

	assert(PopulationData::gen != nullptr); 
    assert(PopulationData::dis != nullptr);
}

void PopulationData::testFitnessFunction(const std::string&
	testPassword, const std::string& halfFitnessVersion) const {
	float perfectFitness = fitnessFunction(testPassword, testPassword);
	float halfFitness = fitnessFunction(testPassword, halfFitnessVersion);
	float badFitness = fitnessFunction(testPassword, "test");

	std::cout << "Perfect fitness: " << perfectFitness << ", "
		<< "half fitness: " << halfFitness << ", bad fitness: "
		<< badFitness << ".\n";

	assert(perfectFitness == 100.0f);
	assert(halfFitness > 50.0f && halfFitness < 100.0f);
	assert(badFitness < 0.0f);
}

void PopulationData::measurePerfAndTestSort(const std::string&
	testPassword) {
	computePerfPopulation(testPassword);

	bool properOrder = true;
	for (int i = 1; i < populationSize-1; i++) {
		auto& curr = currentGeneration[i],
			prev = currentGeneration[i-1];
		if (prev.performance < curr.performance) {
			properOrder = false;
			break;
		}
	}

	assert(properOrder);
}

float PopulationData::randUnitVal() {
	return (*dis)(*gen);
}

char PopulationData::randomLetterAscii() {
	float unitVal = PopulationData::randUnitVal();
	return (char)(97 + (int)(26.0f*unitVal));
}

