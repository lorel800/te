#include "statusbar.h"

int status_load(const std::string& filename, const std::string& status, const std::string& version, int maxx){
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    // Затираем верхнюю строку для полной очистки перед печатью
    mvhline(0, 0, ' ', maxx);
    // Выводим информацию, используя c_str() для безопасности
    mvprintw(0, 0, "WPtext v%-4s|filename: %-32s|status: %s", version.c_str(), filename.c_str(), status.c_str());
    attroff(COLOR_PAIR(1));
    return 0;
}
