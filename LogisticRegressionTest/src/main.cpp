#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <filesystem>
#include <cassert>

#define TARGET_IMAGE_SIZE 256
#define EXPECTED_CHANNELS 3

char* TryGetArgument(int argIndex, int argc, char **argv);
void PrintUsage();
std::vector<std::string> GetFilesInPath(const std::string& path);
void BuildDatasetInformation(const std::string& positiveLabel,
                             const std::string& parentFolder,
                             std::vector<unsigned char*> images,
                             std::vector<float> yValues);
void ResizeNearest(const unsigned char* src, int oldWidth, int oldHeight, int channels,
                   unsigned char* dst, int newWidth, int newHeight);
void FlattenImages(const std::vector<unsigned char*>& images);
void FreeImages(const std::vector<unsigned char*>& images);

void Normalize(const std::vector<unsigned char*>& images);

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
    std::cout << "Reading training images.\n";
    BuildDatasetInformation(positiveLabel,
                            trainingPath,
                            trainingSet,
                            trainingSetY);
    std::cout << "Done.\n";
    std::vector<unsigned char*> testSet;
    std::vector<float> testSetY;
    std::cout << "Reading test images.\n";
    BuildDatasetInformation(positiveLabel,
                            testPath,
                            testSet,
                            testSetY);
    std::cout << "Done.\n";
    
    size_t mTrain = trainingSet.size();
    size_t mTest = testSet.size();
    std::cout << "Number of training examples: " << mTrain
    << ", number of testing examples: " << mTest
    << ", width and height of each image: " << TARGET_IMAGE_SIZE << " x " << TARGET_IMAGE_SIZE
    << ", num channels: " << EXPECTED_CHANNELS << "\n";
    
    std::cout << "Flattening images.\n";
    FlattenImages(trainingSet);
    FlattenImages(testSet);
    std::cout << "Done flattening.\n";
    
    std::cout << "Normalizing...\n";
    Normalize(trainingSet);
    Normalize(testSet);
    std::cout << "Done normalizing.\n";

    FreeImages(trainingSet);
    trainingSet.clear();
    FreeImages(testSet);
    testSet.clear();
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
        assert(channels == EXPECTED_CHANNELS);
        if (img == nullptr) {
            std::cerr << "Could not load image at path " << path << ".\n";
            return 1;
        }
        unsigned char* output = new unsigned char[TARGET_IMAGE_SIZE*TARGET_IMAGE_SIZE*EXPECTED_CHANNELS];
        int input_stride = width * channels;
        int output_stride = TARGET_IMAGE_SIZE * channels;
        // force a resize
        ResizeNearest(img, width, height, channels, output, TARGET_IMAGE_SIZE, TARGET_IMAGE_SIZE);
        images.push_back(output);
        yValues.push_back(yValue);
        stbi_image_free(img);
    }
}

void ResizeNearest(const unsigned char* src, int oldWidth, int oldHeight, int channels,
                   unsigned char* dst, int newWidth, int newHeight) {
    for (int y = 0; y < newHeight; ++y) {
        int src_y = y * oldHeight / newHeight;
        for (int x = 0; x < newWidth; ++x) {
            int src_x = x * oldWidth / newWidth;
            for (int c = 0; c < channels; ++c) {
                dst[(y * newWidth + x) * channels + c] =
                    src[(src_y * oldWidth + src_x) * channels + c];
            }
        }
    }
}

// flatten each image so that the red components are first,
// followed by green and then blue.
void FlattenImages(const std::vector<unsigned char*>& images)
{
    std::vector<unsigned char> tempImage;
    int imageSizeSquared = TARGET_IMAGE_SIZE*TARGET_IMAGE_SIZE;
    int numBytes = imageSizeSquared*EXPECTED_CHANNELS;
    tempImage.resize(numBytes);
    for (size_t i = 0; i < images.size(); i++) {
        for (int row = 0; row < TARGET_IMAGE_SIZE; row++) {
            int rowOffsetOriginal = row*TARGET_IMAGE_SIZE*EXPECTED_CHANNELS;
            int redOffsetDest = row*TARGET_IMAGE_SIZE;
            int greenOffsetDest = imageSizeSquared + redOffsetDest;
            int blueOffsetDest = 2 * imageSizeSquared + redOffsetDest;
            auto image = images[i];
            for (int col = 0; col < TARGET_IMAGE_SIZE; col++) {
                tempImage[redOffsetDest + col] = image[rowOffsetOriginal + col*EXPECTED_CHANNELS];
                tempImage[greenOffsetDest + col] = image[rowOffsetOriginal + col*EXPECTED_CHANNELS + 1];
                tempImage[blueOffsetDest + col] = image[rowOffsetOriginal + col*EXPECTED_CHANNELS + 2];
            }
        }
        memcpy(images[i], tempImage.data(), numBytes);
    }
}

void FreeImages(const std::vector<unsigned char*>& images) {
    for(auto img : images) {
        delete [] img;
    }
}

void Normalize(const std::vector<unsigned char*>& images) {
    int numPixels = TARGET_IMAGE_SIZE*TARGET_IMAGE_SIZE;
    float normFactor = 1.0f/255.0f;
    for (size_t i = 0; i < images.size(); i++) {
        auto& currentImage = images[i];
        for (int px = 0; px < numPixels; px++) {
            currentImage[px] *= normFactor;
        }
    }
}
