#include "display.h"

void displayText(const std::vector<std::wstring>& lines, int cursorY, int cursorX, int scrollOffset) {
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    int displayableLines = maxy - 2;

    for (int i = 0; i < displayableLines; i++) {
        int lineIndex = i + scrollOffset;

        move(i + 2, 0); 
        clrtoeol();

        if (lineIndex < (int)lines.size()) {
            mvprintw(i + 2, 0, "%4i|", lineIndex + 1);
            // Используем mvaddwstr для вывода широких символов
            mvaddwstr(i + 2, 5, lines[lineIndex].c_str());
        }
    }
    
    move(cursorY - scrollOffset + 2, cursorX + 5); 
    refresh();
}