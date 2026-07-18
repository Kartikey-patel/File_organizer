#pragma once
#include<vector>
#include"FileInfo.h"
#include<unordered_map>

class Organizer{
    private:
        std::vector<FileInfo>files;
        std::filesystem::path rootDirectory;
        std::unordered_map<std::string, std::string> extensionMap = {
            {".pdf" ,"PDF"},
            {".jpg" ,"Images"},
            {".jpeg","Images"},
            {".png" ,"Images"},
            {".cpp" ,"CPP"},
            {".h"   ,"CPP"},
            {".txt" ,"Documents"},
            {".ipynb", "Jupyter"},
            {".java", "Java"},
            {".docx", "doc"},
            {".zip" ,"Archives"}};
        std::unordered_map<std::string,int>categoryCount;
    public:
        void scanDirectory(const std::filesystem:: path& path);

        void displayFiles() const;

        std::string getCategory(const FileInfo& file)const;

        std::filesystem::path createCategoryFolder(const std::string& s);

        void moveFile(const std::filesystem::path& oldPath,const std::filesystem::path& newPath);

        void organizer();

        void summary();
};  