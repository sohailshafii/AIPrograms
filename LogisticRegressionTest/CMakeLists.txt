cmake_minimum_required (VERSION 2.9)
project (LogisticRegressionTest)

set (LogisticRegressionTest_VERSION_MAJOR 1)
set (LogisticRegressionTest_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(LogisticRegressionTest ${SOURCE_FILES})

target_include_directories(LogisticRegressionTest
	PRIVATE
		"${PROJECT_BINARY_DIR}"
		"${PROJECT_SOURCE_DIR}/src/")


