#include "filesuite/features/organizer/OrganizerRules.h"

#include <algorithm>
#include <cctype>

namespace filesuite::features::organizer {

OrganizerRules::OrganizerRules()
    : extensionMap_{
        {".pdf", "Documents"},
        {".doc", "Documents"},
        {".docx", "Documents"},
        {".txt", "Documents"},
        {".jpg", "Images"},
        {".jpeg", "Images"},
        {".png", "Images"},
        {".gif", "Images"},
        {".svg", "Images"},
        {".cpp", "Code"},
        {".h", "Code"},
        {".hpp", "Code"},
        {".c", "Code"},
        {".py", "Code"},
        {".java", "Code"},
        {".js", "Code"},
        {".html", "Code"},
        {".css", "Code"},
        {".zip", "Archives"},
        {".rar", "Archives"},
        {".7z", "Archives"},
        {".tar", "Archives"},
        {".gz", "Archives"}
    } {
}

std::string OrganizerRules::getCategory(
    const filesuite::core::FileEntry& file
) const {

    std::string extension = file.extension();

    // Normalize extension to lowercase.
    std::transform(
        extension.begin(),
        extension.end(),
        extension.begin(),
        [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        }
    );

    auto it = extensionMap_.find(extension);

    if (it != extensionMap_.end()) {
        return it->second;
    }

    return "Others";
}

}