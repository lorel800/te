#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <locale>

int filesave(const std::vector<std::wstring>& lines, const std::string& filename);
int fileload(std::vector<std::wstring>& lines, const std::string& filename);

#endif