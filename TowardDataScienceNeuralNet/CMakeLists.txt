cmake_minimum_required (VERSION 2.6)
project (TowardDataScienceNeuralNet)

set(CMAKE_BUILD_TYPE Debug)

set (TowardDataScienceNeuralNet_VERSION_MAJOR 1)
set (TowardDataScienceNeuralNet_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/NeuralNetwork.cpp
	${PROJECT_SOURCE_DIR}/src/NeuralNetwork.h ${PROJECT_SOURCE_DIR}/src/Matrix.cpp
	${PROJECT_SOURCE_DIR}/src/Matrix.h ${PROJECT_SOURCE_DIR}/src/Common.h)

add_executable(TowardDataScienceNeuralNet ${SOURCE_FILES})

target_include_directories(TowardDataScienceNeuralNet
	PRIVATE
		"${PROJECT_BINARY_DIR}"
		"${PROJECT_SOURCE_DIR}/src/")


