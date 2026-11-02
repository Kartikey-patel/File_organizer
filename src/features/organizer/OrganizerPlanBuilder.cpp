
#include "filesuite/features/organizer/OrganizerPlanBuilder.h"

namespace filesuite::features::organizer {

OrganizerPlan OrganizerPlanBuilder::build(
    const std::filesystem::path& directory
) const {

    OrganizerPlan plan;

    const auto scanResult = scanner_.scan(directory);

    for (const auto& issue : scanResult.issues) {
        plan.issues.emplace_back(issue.path, issue.error);
    }

    for (const auto& file : scanResult.files) {

        const std::string category = rules_.getCategory(file);

        const auto destination =
            directory / category / file.path().filename();

        plan.moves.push_back({
            file.path(),
            destination,
            category,
            MoveStatus::Ready
        });
    }

    return plan;
}

}
