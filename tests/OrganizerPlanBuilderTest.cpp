
#include "filesuite/features/organizer/OrganizerPlanBuilder.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;



int main() {

    using filesuite::features::organizer::MoveStatus;
    using filesuite::features::organizer::OrganizerPlan;
    using filesuite::features::organizer::PlannedMove;

    OrganizerPlan statusTest;

    statusTest.moves = {
        {"a.cpp", "Code/a.cpp", "Code", MoveStatus::Ready},
        {"b.cpp", "Code/b.cpp", "Code", MoveStatus::Ready},
        {"c.pdf", "Documents/c.pdf", "Documents", MoveStatus::Conflict},
        {"d.jpg", "Images/d.jpg", "Images", MoveStatus::NoOp}
    };
      
    assert(statusTest.readyCount() == 2);
    assert(statusTest.conflictCount() == 1);
    assert(statusTest.noOpCount() == 1);
    const fs::path testDir = "organizer_plan_test";

    fs::remove_all(testDir);
    fs::create_directories(testDir);

    std::ofstream(testDir / "main.cpp") << "int main() {}";
    std::ofstream(testDir / "report.pdf") << "PDF";
    std::ofstream(testDir / "photo.jpg") << "Image";
    std::ofstream(testDir / "archive.zip") << "ZIP";

    filesuite::features::organizer::OrganizerPlanBuilder builder;

    auto plan = builder.build(testDir);

    assert(plan.moves.size() == 4);

    for (const auto& move : plan.moves) {
        assert(move.destination.parent_path().filename() == move.category);
        assert(move.destination.filename() == move.source.filename());

        std::cout
            << move.source.filename().string()
            << " -> "
            << move.category
            << "/"
            << move.destination.filename().string()
            << '\n';
    }

    // Planning must not modify or move the original files.
    assert(fs::exists(testDir / "main.cpp"));
    assert(fs::exists(testDir / "report.pdf"));
    assert(fs::exists(testDir / "photo.jpg"));
    assert(fs::exists(testDir / "archive.zip"));

    fs::remove_all(testDir);

    std::cout << "All OrganizerPlanBuilder tests passed!\n";

    return 0;
}

