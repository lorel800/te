#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include <ncursesw/ncurses.h>

void displayText(const std::vector<std::wstring>& lines, int cursorY, int cursorX, int scrollOffset);

#endif
