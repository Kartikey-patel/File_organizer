
#include "filesuite/features/organizer/OrganizerPlanBuilder.h"

namespace filesuite::features::organizer {

OrganizerPlan OrganizerPlanBuilder::build(
    const std::filesystem::path& directory
) const {

    OrganizerPlan plan;

    auto scanResult = scanner_.scan(directory);

    // Preserve errors from directory scanning.
    for (const auto& issue : scanResult.issues) {
        plan.issues.emplace_back(issue.path, issue.error);
    }

    for (const auto& file : scanResult.files) {

        const std::string category = rules_.getCategory(file);

        const auto destination =
            directory / category / file.path().filename();

        MoveStatus status = MoveStatus::Ready;

        // Detect a source and destination that refer to the same file.
        std::error_code ec;
        const bool sameFile = std::filesystem::equivalent(
            file.path(),
            destination,
            ec
        );

        if (ec) {
            plan.issues.emplace_back(destination, ec);
        }
        else if (sameFile) {
            status = MoveStatus::NoOp;
        }
        else {
            // Check whether the destination is already occupied.
            const bool destinationExists =
                std::filesystem::exists(destination, ec);

            if (ec) {
                plan.issues.emplace_back(destination, ec);
            }
            else if (destinationExists) {
                status = MoveStatus::Conflict;
            }
        }

        plan.moves.push_back({
            file.path(),
            destination,
            category,
            status
        });
    }

    return plan;
}

}
