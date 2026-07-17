#include <iostream>
#include <filesystem>
#include "Organizer.h"

int main(int argc, char* argv[]) {
    std::filesystem::path directoryPath(argv[1]);

    Organizer org;

    org.scanDirectory(directoryPath);
    org.organizer();

    return 0;
}