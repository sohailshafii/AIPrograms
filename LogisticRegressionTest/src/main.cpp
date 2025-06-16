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

int main(int argc, char** argv)
{
    std::string trainingPath = "";
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
        if (!strcmp(argv[i], "-posLabel")){
            auto positiveLabelVal = TryGetArgument(i + 1, argc, argv);
            if (positiveLabelVal == nullptr) {
                std::cerr << "No positive label value given.\n";
                return 1;
            }
            positiveLabel = positiveLabelVal;
        }
	}
    
    if (trainingPath == "" || positiveLabel == "") {
        PrintUsage();
        return 1;
    }

    std::vector<std::string> trainingPaths = GetFilesInPath(trainingPath);
    std::cout << "Found " << trainingPaths.size() << " training images.\n";
    for(auto path : trainingPaths) {
        int width, height, channels;
        unsigned char* img = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (img == nullptr) {
            std::cerr << "Could not load image at path " << path << ".\n";
            return 1;
        }
        stbi_image_free(img);
    }

	return 0;
}

char* TryGetArgument(int argIndex, int argc, char **argv) {
    if (argIndex == argc){
        return nullptr;
    }
    return argv[argIndex];
}

void PrintUsage() {
    std::cout << "Arguments expected: -train <training_path> -posLabel <positive_label>\n";
}


std::vector<std::string> GetFilesInPath(const std::string& path) {
    std::vector<std::string> allPaths;
    int numFiles;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        allPaths.push_back(entry.path());
    }
    return allPaths;
}
