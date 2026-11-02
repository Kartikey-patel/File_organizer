#include "filesuite/features/organizer/OrganizerPlan.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>

namespace filesuite::features::organizer {

std::size_t OrganizerPlan::readyCount() const {
    std::size_t count = 0;

    for (const auto& move : moves) {
        if (move.status == MoveStatus::Ready) {
            ++count;
        }
    }

    return count;
}

std::size_t OrganizerPlan::conflictCount() const {
    std::size_t count = 0;

    for (const auto& move : moves) {
        if (move.status == MoveStatus::Conflict) {
            ++count;
        }
    }

    return count;
}

std::size_t OrganizerPlan::noOpCount() const {
    std::size_t count = 0;

    for (const auto& move : moves) {
        if (move.status == MoveStatus::NoOp) {
            ++count;
        }
    }

    return count;
}   

}