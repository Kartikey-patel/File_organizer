#include "filesuite/core/filesystem/DirectoryScanner.h"

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {

    fs::path testDir = "scanner_test";

    // Create temporary directory
    fs::create_directories(testDir);

    // Create test files
    std::ofstream(testDir / "file1.txt") << "Hello";
    std::ofstream(testDir / "file2.cpp") << "C++";
    std::ofstream(testDir / "file3.pdf") << "PDF";

    // Run scanner
    filesuite::core::DirectoryScanner scanner;

    auto result = scanner.scan(testDir);

    // Display results
    std::cout << "Files scanned: " << result.files.size() << '\n';

    for (const auto& file : result.files) {
        std::cout << file.name()
                  << " | "
                  << file.extension()
                  << " | "
                  << file.size() << " bytes\n";
    }

    std::cout << "Issues: " << result.issues.size() << '\n';

    // Cleanup
    fs::remove_all(testDir);
    // Test 2: Empty directory
    fs::path emptyDir = "scanner_empty_test";
    fs::create_directories(emptyDir);
      
    auto emptyResult = scanner.scan(emptyDir);
      
    if (!emptyResult.files.empty()) {
        std::cerr << "Empty directory test failed\n   ";
        return 1;
    }
    
    // Test 3: Non-existent directory
    fs::path invalidDir = "directory_that_does_not_exist";
    
    auto invalidResult = scanner.scan(invalidDir);
    
    if (invalidResult.issues.empty()) {
        std::cerr << "Invalid directory test failed\n   ";
        return 1;
    }
    
    std::cout << "All scanner tests passed!\n   ";
    
    fs::remove_all(emptyDir);

    return 0;
}