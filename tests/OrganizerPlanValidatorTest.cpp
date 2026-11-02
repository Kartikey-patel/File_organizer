
#include "filesuite/features/organizer/OrganizerPlanValidator.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

using filesuite::features::organizer::MoveStatus;
using filesuite::features::organizer::OrganizerPlan;
using filesuite::features::organizer::OrganizerPlanValidator;
using filesuite::features::organizer::PlannedMove;

int main() {

    const fs::path root = "validator_test";

    fs::remove_all(root);
    fs::create_directories(root / "Code");

    // Create source files.
    std::ofstream(root / "ready.cpp") << "Ready";
    std::ofstream(root / "conflict.cpp") << "Source";
    std::ofstream(root / "Code" / "conflict.cpp") << "Existing";
    std::ofstream(root / "noop.cpp") << "No operation";
    std::ofstream(root / "first.cpp") << "First";
    std::ofstream(root / "second.cpp") << "Second";

    OrganizerPlan plan;

    plan.moves = {
        {
            root / "ready.cpp",
            root / "Code" / "ready.cpp",
            "Code",
            MoveStatus::Ready
        },
        {
            root / "conflict.cpp",
            root / "Code" / "conflict.cpp",
            "Code",
            MoveStatus::Ready
        },
        {
            root / "noop.cpp",
            root / "noop.cpp",
            "Code",
            MoveStatus::Ready
        },
        {
            root / "first.cpp",
            root / "Code" / "shared.cpp",
            "Code",
            MoveStatus::Ready
        },
        {
            root / "second.cpp",
            root / "Code" / "shared.cpp",
            "Code",
            MoveStatus::Ready
        }
    };

    OrganizerPlanValidator validator;
    validator.validate(plan);

    assert(plan.moves[0].status == MoveStatus::Ready);
    assert(plan.moves[1].status == MoveStatus::Conflict);
    assert(plan.moves[2].status == MoveStatus::NoOp);
    assert(plan.moves[3].status == MoveStatus::Conflict);
    assert(plan.moves[4].status == MoveStatus::Conflict);

    assert(plan.readyCount() == 1);
    assert(plan.conflictCount() == 3);
    assert(plan.noOpCount() == 1);

    // Validation must not modify the filesystem.
    assert(fs::exists(root / "ready.cpp"));
    assert(fs::exists(root / "conflict.cpp"));
    assert(fs::exists(root / "Code" / "conflict.cpp"));
    assert(fs::exists(root / "first.cpp"));
    assert(fs::exists(root / "second.cpp"));

    std::cout << "All OrganizerPlanValidator tests passed!\n";

    fs::remove_all(root);

    return 0;
}
