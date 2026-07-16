#include"FileInfo.h"
#include<iostream>

FileInfo::FileInfo(const std::filesystem::path& path) : path(path)
{
}

std::string FileInfo::getName() const{
    return path.filename().string(); // filename return path
}

std::string FileInfo::getExtension() const{
    return path.extension().string();
}

std:: uintmax_t FileInfo::getSize() const{
    return std::filesystem::file_size(path); 
}

void FileInfo::display() const{
    std::cout << "- - - - - - - - - - - - - - - -\n";
    std::cout << getName() << '\n';
    std::cout << getExtension() << '\n';
    std::cout << getSize() <<" bytes\n";
    std::cout << "- - - - - - - - - - - - - - - -\n";
}