#pragma once

#include "filesuite/core/filesystem/DirectoryScanner.h"
#include "filesuite/features/organizer/OrganizerPlan.h"
#include "filesuite/features/organizer/OrganizerRules.h"

#include <filesystem>

namespace filesuite::features::organizer {

class OrganizerPlanBuilder {
private:
    filesuite::core::DirectoryScanner scanner_;
    OrganizerRules rules_;

public:
    OrganizerPlan build(const std::filesystem::path& directory) const;
};

}