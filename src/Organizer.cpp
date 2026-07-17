#include"Organizer.h"
#include<iostream>

void Organizer::scanDirectory(const std::filesystem:: path& path){
    rootDirectory = path;
    files.clear();
    if(std::filesystem::exists(path) && std::filesystem::is_directory(path)){
        for(const auto& entry : std::filesystem::directory_iterator(path)){
            if(entry.is_regular_file())
                files.emplace_back(entry.path());
        }
    }
    else{
        std::cout << "Directory doesnot exist\n";
    }
}

std::string Organizer::getCategory(const FileInfo& file) const {
    std::string category = file.getExtension();
    if(extensionMap.find(category) != extensionMap.end()){
        return extensionMap.at(category);
    }
    else
        return "others"; 
}

std::filesystem::path Organizer::createCategoryFolder(const std::string& s){
    std::filesystem::path dir = rootDirectory / s;
    if(!std::filesystem::exists(dir)){
        std::filesystem::create_directory(dir);
    }
    return dir;
}

void Organizer::organizer(){
    for(const auto& file : files){
        std::string category = getCategory(file);
        std::filesystem::path p = createCategoryFolder(category);
        std::filesystem::path oldPath = file.getPath();
        std::string name = file.getName();
        std::filesystem::path newPath = p / name;
        moveFile(oldPath,newPath);
    }
}

void Organizer::moveFile(const std::filesystem::path& oldPath,const std::filesystem::path& newPath ){
    std::filesystem::rename(oldPath,newPath);
}

void Organizer::displayFiles() const{
    if(files.empty()){
        std::cout <<"No file found\n"; 
    }
    else{
        for(const auto& it : files){
            it.display();
        }
    }
}