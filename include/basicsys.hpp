#pragma once
#include <string>

struct FileInfo {
    std::string fileName;
    std::string fileExtension;
    bool isSelected = false;
    bool isDirectory = false;
}; // A file info struct used to store file information.

void OpenSourceFile(std::string directory, std::string fileName, std::string fileExtension);