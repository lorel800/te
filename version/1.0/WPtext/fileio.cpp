#include "fileio.h"
#include <iostream>

int filesave(const std::vector<std::wstring>& lines, const std::string& filename) {
    std::filesystem::path path_to_file = filename;
    std::wofstream file(path_to_file);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return 1;
    }
    
    // Устанавливаем локаль для правильного сохранения широких символов
    file.imbue(std::locale(""));
    
    for (const auto& line : lines) {
        file << line << std::endl;
    }

    return 0;
}

int fileload(std::vector<std::wstring>& lines, const std::string& filename) {
    std::filesystem::path _path = filename;
    try {
        _path = std::filesystem::absolute(_path);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error with file path: " << e.what() << std::endl;
        return 1;
    }
    
    if (!std::filesystem::exists(_path)) {
        std::ofstream outfile(_path);
        if (!outfile.is_open()) {
            std::cerr << "Error: Could not create file." << std::endl;
            return 1;
        }
        outfile.close();
    }
    
    std::wifstream inputFile(_path);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file for reading." << std::endl;
        return 1;
    }
    
    // Устанавливаем локаль для правильного чтения широких символов
    inputFile.imbue(std::locale(""));
    
    std::wstring line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    
    return 0;
}
