#include"FileInfo.h"
#include<iostream>

FileInfo::FileInfo(const std::filesystem::path& path) : path(path)
{
}

std::string FileInfo::getName() const{
    return path.filename().string(); // filename return path
}

void FileInfo::display() const{
    std::cout << getName() << '\n';
}