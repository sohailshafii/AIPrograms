#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <filesystem>

char* TryGetArgument(int argIndex, int argc, char **argv);
void PrintUsage();
std::vector<std::string> GetFilesInPath(const std::string& path);
void BuildDatasetInformation(const std::string& positiveLabel,
                             const std::string& parentFolder,
                             std::vector<unsigned char*> images,
                             std::vector<float> yValues);
void FreeImages(const std::vector<unsigned char*>& trainingSet);

int main(int argc, char** argv)
{
    std::string trainingPath = "";
    std::string testPath = "";
    std::string positiveLabel = "";
	for (int i = 1; i < argc; i++){
        if (!strcmp(argv[i], "-train")) {
            auto trainingPathVal = TryGetArgument(i + 1, argc, argv);
            if (trainingPathVal == nullptr) {
                std::cerr << "No training path argument given.\n";
                return 1;
            }
            trainingPath = trainingPathVal;
        }
        if (!strcmp(argv[i], "-test")){
            auto testPathVal = TryGetArgument(i + 1, argc, argv);
            if (testPathVal == nullptr) {
                std::cerr << "No test path given.\n";
                return 1;
            }
            testPath = testPathVal;
        }
        if (!strcmp(argv[i], "-posLabel")){
            auto positiveLabelVal = TryGetArgument(i + 1, argc, argv);
            if (positiveLabelVal == nullptr) {
                std::cerr << "No positive label value given.\n";
                return 1;
            }
            positiveLabel = positiveLabelVal;
        }
	}
    
    if (trainingPath == "" || testPath == "" || positiveLabel == "") {
        PrintUsage();
        return 1;
    }

    std::vector<unsigned char*> trainingSet;
    std::vector<float> trainingSetY;
    BuildDatasetInformation(positiveLabel,
                            trainingPath,
                            trainingSet,
                            trainingSetY);
    std::vector<unsigned char*> testSet;
    std::vector<float> testSetY;
    BuildDatasetInformation(positiveLabel,
                            testPath,
                            testSet,
                            testSetY);

    FreeImages(trainingSet);
	return 0;
}

char* TryGetArgument(int argIndex, int argc, char **argv) {
    if (argIndex == argc){
        return nullptr;
    }
    return argv[argIndex];
}

void PrintUsage() {
    std::cout << "Arguments expected: -train <training_path> -test <test_path> -posLabel <positive_label>\n";
}

std::vector<std::string> GetFilesInPath(const std::string& path) {
    std::vector<std::string> allPaths;
    int numFiles;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        allPaths.push_back(entry.path());
    }
    return allPaths;
}

void BuildDatasetInformation(const std::string& positiveLabel,
         const std::string& parentFolder,
         std::vector<unsigned char*> images,
         std::vector<float> yValues) {
    std::vector<std::string> filePaths = GetFilesInPath(parentFolder);
    std::cout << "Found " << filePaths.size() << " images in path " << parentFolder << ".\n";
    for(auto path : filePaths) {
        int width, height, channels;
        // positive means Y = 1, otherwise it is 0.
        float yValue = path.find(positiveLabel) != std::string::npos ? 1.0f : 0.0f;
        unsigned char* img = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (img == nullptr) {
            std::cerr << "Could not load image at path " << path << ".\n";
            return 1;
        }
        images.push_back(img);
        yValues.push_back(yValue);
    }
}

void FreeImages(const std::vector<unsigned char*>& trainingSet) {
    for(auto img : trainingSet) {
        stbi_image_free(img);
    }
}
