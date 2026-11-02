
#include "filesuite/features/organizer/OrganizerPlanValidator.h"

#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <vector>

namespace filesuite::features::organizer {

namespace {

std::string normalizedPath(
    const std::filesystem::path& path,
    std::error_code& ec
) {
    auto absolutePath = std::filesystem::absolute(path, ec);

    if (ec) {
        return {};
    }

    std::string key =
        absolutePath.lexically_normal().generic_string();

#ifdef _WIN32
    std::transform(
        key.begin(),
        key.end(),
        key.begin(),
        [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        }
    );
#endif

    return key;
}

}

void OrganizerPlanValidator::validate(OrganizerPlan& plan) const {

    // First validate each individual move.
    for (auto& move : plan.moves) {

        if (move.status == MoveStatus::NoOp) {
            continue;
        }

        std::error_code ec;

        const auto sourceKey = normalizedPath(move.source, ec);

        if (ec) {
            plan.issues.emplace_back(move.source, ec);
            move.status = MoveStatus::Conflict;
            continue;
        }

        const auto destinationKey =
            normalizedPath(move.destination, ec);

        if (ec) {
            plan.issues.emplace_back(move.destination, ec);
            move.status = MoveStatus::Conflict;
            continue;
        }

        // Same normalized path means no movement is necessary.
        if (sourceKey == destinationKey) {
            move.status = MoveStatus::NoOp;
            continue;
        }

        // Check whether the destination already exists.
        const bool destinationExists =
            std::filesystem::exists(move.destination, ec);

        if (ec) {
            plan.issues.emplace_back(move.destination, ec);
            move.status = MoveStatus::Conflict;
            continue;
        }

        if (destinationExists) {

            // Different paths can still refer to the same file
            // (for example, through hard links).
            const bool sameFile = std::filesystem::equivalent(
                move.source,
                move.destination,
                ec
            );

            if (ec) {
                plan.issues.emplace_back(move.destination, ec);
                move.status = MoveStatus::Conflict;
            }
            else if (sameFile) {
                move.status = MoveStatus::NoOp;
            }
            else {
                move.status = MoveStatus::Conflict;
            }
        }
        else {
            move.status = MoveStatus::Ready;
        }
    }

    // Now detect collisions between planned destinations.
    std::unordered_map<std::string, std::vector<std::size_t>>
        destinationGroups;

    for (std::size_t i = 0; i < plan.moves.size(); ++i) {

        const auto& move = plan.moves[i];

        // No-op moves do not occupy a planned destination.
        if (move.status == MoveStatus::NoOp) {
            continue;
        }

        std::error_code ec;

        const auto key = normalizedPath(move.destination, ec);

        if (ec) {
            plan.issues.emplace_back(move.destination, ec);
            plan.moves[i].status = MoveStatus::Conflict;
            continue;
        }

        destinationGroups[key].push_back(i);
    }

    // Every move targeting the same destination becomes a conflict.
    for (const auto& [key, indices] : destinationGroups) {

        if (indices.size() < 2) {
            continue;
        }

        for (const auto index : indices) {
            plan.moves[index].status = MoveStatus::Conflict;
        }
    }
}

}
