#pragma once

#include <filesystem>
#include <cstdint>
#include <string>

namespace filesuite::core {

class FileEntry {
private:
    std::filesystem::path path_;
    std::uintmax_t size_;

public:
    FileEntry(std::filesystem::path path, std::uintmax_t size);

    const std::filesystem::path& path() const noexcept;

    std::string name() const;
    std::string extension() const;

    std::uintmax_t size() const noexcept;
};

}