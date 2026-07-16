#include <iostream>
#include <filesystem>
#include "Organizer.h"

int main(int argc, char* argv[]) {
    std::filesystem::path directoryPath(argv[1]);

    Organizer organizer;

    organizer.scanDirectory(directoryPath);
    organizer.displayFiles();

    return 0;
}