
#pragma once

#include <filesystem>
#include <string>
#include <system_error>
#include <vector>
#include <utility>

namespace filesuite::features::organizer {

enum class MoveStatus {
    Ready,
    Conflict,
    NoOp
};

struct PlannedMove {
    std::filesystem::path source;
    std::filesystem::path destination;
    std::string category;
    MoveStatus status = MoveStatus::Ready;
};

struct OrganizerPlan {
    std::vector<PlannedMove> moves;
    std::vector<std::pair<std::filesystem::path, std::error_code>> issues;

    std::size_t readyCount() const;
    std::size_t conflictCount() const;
    std::size_t noOpCount() const;

};

}
