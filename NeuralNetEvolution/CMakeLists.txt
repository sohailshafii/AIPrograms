cmake_minimum_required (VERSION 2.6)
project (NeuralNetEvolution)

set (NeuralNetEvolution_VERSION_MAJOR 1)
set (NeuralNetEvolution_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(NeuralNetEvolution ${SOURCE_FILES})

target_include_directories(NeuralNetEvolution
	PRIVATE
		"${PROJECT_BINARY_DIR}"
		"${PROJECT_SOURCE_DIR}/src/")


