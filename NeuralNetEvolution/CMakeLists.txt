cmake_minimum_required (VERSION 2.9)
project (NeuralNetEvolution)

set (NeuralNetEvolution_VERSION_MAJOR 1)
set (NeuralNetEvolution_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/Common.cpp  ${PROJECT_SOURCE_DIR}/src/Common.h ${PROJECT_SOURCE_DIR}/src/NeuralNetwork.h ${PROJECT_SOURCE_DIR}/src/NeuralNetwork.cpp ${PROJECT_SOURCE_DIR}/src/Individual.h ${PROJECT_SOURCE_DIR}/src/Individual.cpp)

add_executable(NeuralNetEvolution ${SOURCE_FILES})

target_include_directories(NeuralNetEvolution
	PRIVATE
		"${PROJECT_BINARY_DIR}"
		"${PROJECT_SOURCE_DIR}/src/")


