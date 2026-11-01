#include "filesuite/core/filesystem/FileEntry.h"

#include <utility>

namespace filesuite::core {

FileEntry::FileEntry(std::filesystem::path path, std::uintmax_t size)
    : path_(std::move(path)), size_(size) {
}

const std::filesystem::path& FileEntry::path() const noexcept {
    return path_;
}

std::string FileEntry::name() const {
    return path_.filename().string();
}

std::string FileEntry::extension() const {
    return path_.extension().string();
}

std::uintmax_t FileEntry::size() const noexcept {
    return size_;
}

}