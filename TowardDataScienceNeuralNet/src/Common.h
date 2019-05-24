#pragma once

#include <random>

// returns random value between 0 and 1
static float randomUnitValue() {
	static std::random_device rd;  
	// Standard mersenne_twister_engine seeded with rd()
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<>dis(0.0f, 1.0f);

	return dis(gen);
}
