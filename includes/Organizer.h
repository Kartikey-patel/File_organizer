#pragma once
#include<vector>
#include"FileInfo.h"

class Organizer{
    private:
        std::vector<FileInfo>files;
    
    public:
        void scanDirectory(const std::filesystem:: path& path);
        void displayFiles() const;

};