#include <ncursesw/ncurses.h>
#include <clocale>
#include <vector>
#include <string>
#include <algorithm>
#include "textEditor/fileio.h"
#include "textEditor/statusbar.h"
#include "textEditor/display.h"
#include "textEditor/data.h"
#include "textEditor/editor.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 2) {
        endwin();
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

        int result = handle_input(ch, locale_data, lines, cursorY, cursorX, scrollOffset);
        if (result == 0) {
            break;
        }

        status_load(locale_data.filename, locale_data.status, locale_data.version, locale_data.maxX);
        displayText(lines, cursorY, cursorX, scrollOffset);
    }

    endwin();
    return 0;
}