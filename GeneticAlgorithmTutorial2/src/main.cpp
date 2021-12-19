//http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#include <iostream>
#include "Population.h"
#include "Individual.h"
#include "FitnessCalc.h"
#include "Algorithm.h"
#include <cstdlib>
#include <ctime>

int main() {
	srand((unsigned int)time(NULL));
	FitnessCalc::SetSolution("1111000000000000000000000000000000000000000000000000000000001111");

	Population myPop(50, true);

	int generationCount = 0;
	while (myPop.GetFittest().GetFitness() < FitnessCalc::GetMaxFitness()) {
		generationCount++;
		std::cout << " Generation: " << generationCount << ", fittest: "
			<< myPop.GetFittest().GetFitness() << " vs " <<
			FitnessCalc::GetMaxFitness() << ".\n";
		myPop = Algorithm::EvolvePopulation(myPop);
		std::cout << "Evolved!\n";
	}
	std::cout << "Solution found! Generation: " << generationCount
		<< ", genes: \n";
	myPop.GetFittest().Print();

	return 0;
}
