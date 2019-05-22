cmake_minimum_required (VERSION 2.6)
project (GeneticAlgorithmTutorial2)

set (GeneticAlgorithmTutorial2_VERSION_MAJOR 1)
set (GeneticAlgorithmTutorial2_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp
${PROJECT_SOURCE_DIR}/src/Individual.h ${PROJECT_SOURCE_DIR}/src/Individual.cpp ${PROJECT_SOURCE_DIR}/src/Population.h ${PROJECT_SOURCE_DIR}/src/Population.cpp ${PROJECT_SOURCE_DIR}/src/FitnessCalc.h ${PROJECT_SOURCE_DIR}/src/FitnessCalc.cpp)

add_executable(GeneticAlgorithmTutorial2 ${SOURCE_FILES})

target_include_directories(GeneticAlgorithmTutorial2
	PRIVATE
		"${PROJECT_BINARY_DIR}"
		"${PROJECT_SOURCE_DIR}/src/")


