#include "editor.h"
#include "fileio.h"
#include "statusbar.h"
#include <ncursesw/ncurses.h>
#include <algorithm>

int handle_input(wint_t ch, data& locale_data, std::vector<std::wstring>& lines, int& cursorY, int& cursorX, int& scrollOffset) {
    
    getmaxyx(stdscr, locale_data.maxY, locale_data.maxX);

    if (ch == 27) { // Escape
        return 0; 
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
    } else if (ch == 19) { // Ctrl + S
        locale_data.status = "please wait a few time...";
        status_load(locale_data.filename, locale_data.status, locale_data.version, locale_data.maxX);
        refresh();
        filesave(lines, locale_data.filename);
        locale_data.status = "saved";
    } else if (ch == '\t') {

        lines[cursorY].insert(cursorX, 4, L' ');
        cursorX += 4;
    } else {

        lines[cursorY].insert(cursorX, 1, (wchar_t)ch);
        cursorX++;
        locale_data.status = "editing";
    }

    if (cursorX > (int)lines[cursorY].length()) {
        cursorX = lines[cursorY].length();
    }

    return 1;
}
