cmake_minimum_required (VERSION 3.0)
project (TowardDataScienceNeuralNet)


set (TowardDataScienceNeuralNet_VERSION_MAJOR 1)
set (TowardDataScienceNeuralNet_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#[[set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")]]

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/NeuralNetwork.cpp
	${PROJECT_SOURCE_DIR}/src/NeuralNetwork.h ${PROJECT_SOURCE_DIR}/src/Matrix.cpp
	${PROJECT_SOURCE_DIR}/src/Matrix.h ${PROJECT_SOURCE_DIR}/src/Common.h 
	${PROJECT_SOURCE_DIR}/src/Common.cpp)

add_executable(TowardDataScienceNeuralNet ${SOURCE_FILES})

target_include_directories(TowardDataScienceNeuralNet
	PRIVATE
		"${PROJECT_BINARY_DIR}"
		"${PROJECT_SOURCE_DIR}/src/")


