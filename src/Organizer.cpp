#include"Organizer.h"
#include<iostream>

void Organizer::scanDirectory(const std::filesystem:: path& path){
    files.clear();
    if(std::filesystem::exists(path) && std::filesystem::is_directory(path)){
        for(const auto& entry : std::filesystem::directory_iterator(path)){
            if(entry.is_regular_file())
                files.emplace_back(entry.path());
        }
        std::cout << "Directory scaned successfully\n";
    }
    else{
        std::cout << "Directory doesnot exist\n";
    }
}


void Organizer::displayFiles() const{
    if(files.size() == 0){
        std::cout <<"No file found\n"; 
    }
    else{
        for(const auto& it : files){
            it.display();
        }
    }
}