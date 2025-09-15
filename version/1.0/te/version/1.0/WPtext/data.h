#ifndef DATA_H
#define DATA_H

#include <string>

// Структура для хранения данных о состоянии приложения
typedef struct {
    std::string filename;
    std::string status;
    std::string version;
    int maxX;
    int maxY;
} data;

#endif