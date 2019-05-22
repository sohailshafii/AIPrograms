// http://www.theprojectspot.com/tutorial-post/creating-a-genetic-algorithm-for-beginners/3

#include <string>
#include "Individual.h"

class FitnessCalc {
public:
	static int numChars;
	static char* solution;

	static void setSolution(char* newSolution, int length) {
		if (solution != nullptr) {
			delete [] solution;
		}
		numChars = length;
		memcpy(solution, newSolution, length);
	}	

	static void setSolution(const std::string& newSolution) {
		if (solution != nullptr) {
			delete [] solution;
		}
		numChars = newSolution.size();
        solution = new char[numChars];
        const char* charVersion = newSolution.c_str();

        // Loop through each character of our string and save it in our byte 
        // array
        for (int i = 0; i < numChars; i++) {
            auto currChar = charVersion[i]; 
            if (currChar == '0' || currChar == '1') {
                solution[i] = currChar;
            } else {
                solution[i] = 0;
            }
        }
    }

    static int getFitness(const Individual& individual) {
        int fitness = 0;
        int individualSize = individual.size();

        // Loop through our individuals genes and compare them to our cadidates
        for (int i = 0; i < individualSize && i < numChars; i++) {
            if (individual.getGene(i) == solution[i]) {
                fitness++;
            }
        }
        return fitness;
    }

    static int getMaxFitness() {
        return numChars;
    }
};
