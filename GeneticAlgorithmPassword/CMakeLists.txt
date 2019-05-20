cmake_minimum_required (VERSION 2.6)
project (GeneticAlgorithmPassword)

set (GeneticAlgorithmPassword_VERSION_MAJOR 1)
set (GeneticAlgorithmPassword_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/PopulationData.cpp
	${PROJECT_SOURCE_DIR}/src/PopulationData.h)

add_executable(GeneticAlgorithmPassword ${SOURCE_FILES})

target_include_directories(GeneticAlgorithmPassword
	PRIVATE
		"${PROJECT_BINARY_DIR}"
		"${PROJECT_SOURCE_DIR}/src/")

