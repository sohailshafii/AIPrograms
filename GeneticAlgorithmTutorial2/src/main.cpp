#include <iostream>
#include "Population.h"
#include "Individual.h"
#include "FitnessCalc.h"
#include "Algorithm.h"

int main() {
	FitnessCalc::setSolution("1111000000000000000000000000000000000000000000000000000000001111");

	Population myPop(50, true);

	int generationCount = 0;
	while(myPop.getFittest().getFitness() < FitnessCalc::getMaxFitness()) {
		generationCount++;
		std::cout << " Generation: " << generationCount << ", fittest: "
			<< myPop.getFittest().getFitness() << " vs " << 
			FitnessCalc::getMaxFitness() << ".\n";
		myPop = Algorithm::evolvePopulation(myPop);
		std::cout << "Evolved!\n";
	}
	std::cout << "Solution found! Generation: " << generationCount
		<< ", genes: \n";
	myPop.getFittest().print();

	return 0;
}
