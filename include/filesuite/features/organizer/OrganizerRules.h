#pragma once

#include "filesuite/core/filesystem/FileEntry.h"

#include <string>
#include <unordered_map>

namespace filesuite::features::organizer {

class OrganizerRules {
private:
    std::unordered_map<std::string, std::string> extensionMap_;

public:
    OrganizerRules();

    std::string getCategory(
        const filesuite::core::FileEntry& file
    ) const;
};

}