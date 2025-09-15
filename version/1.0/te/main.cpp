#include <ncursesw/ncurses.h>
#include <clocale>
#include <vector>
#include <string>
#include <algorithm>
#include "WPtext/fileio.h"
#include "WPtext/statusbar.h"
#include "WPtext/display.h"
#include "WPtext/data.h"

int main(int argc, char* argv[]) {
    // Устанавливаем локаль для поддержки юникода
    setlocale(LC_ALL, "");
    
    if (argc < 2){
        return 1;
    } 
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    data locale_data;
    locale_data.filename = argv[1];
    locale_data.status = "editing";
    locale_data.version = "1.0";
    getmaxyx(stdscr, locale_data.maxY, locale_data.maxX);
    
    // Используем wstring для работы с широкими символами
    std::vector<std::wstring> lines;

    int load_result = fileload(lines, locale_data.filename);
    
    if (load_result != 0 || lines.empty()) {
        lines.push_back(L"");
    }
    
    int cursorY = 0;
    int cursorX = 0;
    int scrollOffset = 0;
    
    status_load(locale_data.filename, locale_data.status, locale_data.version, locale_data.maxX);
    displayText(lines, cursorY, cursorX, scrollOffset);

    while (true) {
        wint_t ch;
        get_wch(&ch);

        if (ch == 27) { // Escape key
            break;
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (cursorX > 0) {
                lines[cursorY].erase(cursorX - 1, 1);
                cursorX--;
                locale_data.status = "editing";
            } else if (cursorY > 0) {
                cursorX = lines[cursorY - 1].length();
                lines[cursorY - 1] += lines[cursorY];
                lines.erase(lines.begin() + cursorY);
                cursorY--;
                locale_data.status = "editing";
            }
        } else if (ch == KEY_LEFT) {
            if (cursorX > 0) {
                cursorX--;
            } else if (cursorY > 0) {
                cursorY--;
                cursorX = lines[cursorY].length();
            }
            if (cursorY < scrollOffset) {
                scrollOffset--;
            }
        } else if (ch == KEY_RIGHT) {
            if (cursorX < (int)lines[cursorY].length()) {
                cursorX++;
            } else if (cursorY < (int)lines.size() - 1) {
                cursorY++;
                cursorX = 0;
            }
            if (cursorY >= scrollOffset + (locale_data.maxY - 2)) {
                scrollOffset++;
            }
        } else if (ch == KEY_UP) {
            if (cursorY > 0) {
                cursorY--;
            }
            if (cursorY < scrollOffset) {
                scrollOffset--;
            }
            cursorX = std::min(cursorX, (int)lines[cursorY].length());
        } else if (ch == KEY_DOWN) {
            if (cursorY < (int)lines.size() - 1) {
                cursorY++;
            }
            if (cursorY >= scrollOffset + (locale_data.maxY - 2)) {
                scrollOffset++;
            }
            cursorX = std::min(cursorX, (int)lines[cursorY].length());
        } else if (ch == L'\n') {
            std::wstring remaining_text = lines[cursorY].substr(cursorX);
            lines[cursorY] = lines[cursorY].substr(0, cursorX);
            lines.insert(lines.begin() + cursorY + 1, remaining_text);
            cursorY++;
            cursorX = 0;
            if (cursorY >= scrollOffset + (locale_data.maxY - 2)) {
                scrollOffset++;
            }
            locale_data.status = "editing";
        } else if(ch == 19) { // Ctrl + S
            locale_data.status = "please wait a few time...";
            status_load(locale_data.filename, locale_data.status, locale_data.version, locale_data.maxX);
            refresh();
            filesave(lines, locale_data.filename);
            locale_data.status = "saved";
        } else {
            lines[cursorY].insert(cursorX, 1, (wchar_t)ch); 
            cursorX++; 
            locale_data.status = "editing";
        }
        
        if (cursorX > (int)lines[cursorY].length()) {
            cursorX = lines[cursorY].length();
        }

        status_load(locale_data.filename, locale_data.status, locale_data.version, locale_data.maxX);
        displayText(lines, cursorY, cursorX, scrollOffset);
    }

    endwin();
    return 0;
}
