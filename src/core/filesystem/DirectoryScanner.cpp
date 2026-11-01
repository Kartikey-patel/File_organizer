#include "filesuite/core/filesystem/DirectoryScanner.h"

namespace filesuite::core {

ScanResult DirectoryScanner::scan(
    const std::filesystem::path& directory
) const {

    ScanResult result;

    std::error_code ec;

    // Validate and open the directory.
    std::filesystem::directory_iterator iterator(directory, ec);
    const std::filesystem::directory_iterator end;

    if (ec) {
        result.issues.push_back({directory, ec});
        return result;
    }

    // Iterate over directory entries.
    while (iterator != end) {

        const auto& entry = *iterator;
        const auto& path = entry.path();

        // Check the entry type without following symbolic links.
        auto status = entry.symlink_status(ec);

        if (ec) {
            result.issues.push_back({path, ec});
            ec.clear();
        }
        else if (std::filesystem::is_regular_file(status)) {

            // Retrieve file size.
            auto size = entry.file_size(ec);

            if (ec) {
                result.issues.push_back({path, ec});
                ec.clear();
            }
            else {
                result.files.emplace_back(path, size);
            }
        }

        // Move to the next entry.
        iterator.increment(ec);

        if (ec) {
            result.issues.push_back({directory, ec});
            break;
        }
    }

    return result;
}

}