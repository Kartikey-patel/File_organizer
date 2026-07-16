#pragma once
#include <filesystem>
#include<string>


class FileInfo{
    private:
        std::filesystem:: path path;
    
    public:

        FileInfo(const std::filesystem::path& path);

        std::string getName() const;

        void display() const;

};