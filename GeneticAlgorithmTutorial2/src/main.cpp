#include "Population.h"
#include "Individual.h"
#include "FitnessCalc.h"
#include "Algorithm.h"

int main() {
	FitnessCalc::setSolution("1111000000000000000000000000000000000000000000000000000000001111");

	Population myPop(50,true);

	return 0;
}
