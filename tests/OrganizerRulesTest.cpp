#include "filesuite/features/organizer/OrganizerRules.h"

#include <cassert>
#include <iostream>

using filesuite::core::FileEntry;
using filesuite::features::organizer::OrganizerRules;

int main() {
    OrganizerRules rules;

    assert(rules.getCategory(FileEntry("main.cpp", 100)) == "Code");
    assert(rules.getCategory(FileEntry("App.java", 100)) == "Code");
    assert(rules.getCategory(FileEntry("script.PY", 100)) == "Code");
    assert(rules.getCategory(FileEntry("report.pdf", 100)) == "Documents");
    assert(rules.getCategory(FileEntry("photo.JPG", 100)) == "Images");
    assert(rules.getCategory(FileEntry("archive.zip", 100)) == "Archives");
    assert(rules.getCategory(FileEntry("unknown.xyz", 100)) == "Others");
    assert(rules.getCategory(FileEntry("README", 100)) == "Others");

    std::cout << "All OrganizerRules tests passed!\n";
    return 0;
}