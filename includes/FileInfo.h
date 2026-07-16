#pragma once
#include <filesystem>
#include<string>


class FileInfo{
    private:
        std::filesystem:: path path;
    
    public:

        FileInfo(const std::filesystem::path& path);

        std::string getName() const;

        std::string getExtension() const;

        std:: uintmax_t getSize() const;

        void display() const;

};