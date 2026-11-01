#pragma once

#include "filesuite/core/filesystem/FileEntry.h"

#include <filesystem>
#include <system_error>
#include <vector>

namespace filesuite::core {

struct ScanIssue {
    std::filesystem::path path;
    std::error_code error;
};

struct ScanResult {
    std::vector<FileEntry> files;
    std::vector<ScanIssue> issues;

    bool successful() const noexcept {
        return issues.empty();
    }
};

class DirectoryScanner {
public:
    ScanResult scan(const std::filesystem::path& directory) const;
};

}