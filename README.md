# File Organizer

A command-line C++ application that automatically organizes files into folders based on their extensions.

## Features

- Scan a directory
- Categorize files by extension
- Create category folders automatically
- Move files into their respective folders

## Technologies

- C++17
- Standard Template Library (STL)
- std::filesystem

## Project Structure

include/
src/

## Build

g++ -std=c++17 -Iincludes  src/main.cpp src/FileInfo.cpp src/Organizer.cpp -o app

## Run

./app <directory_path>

Example:

./app ~/Downloads
