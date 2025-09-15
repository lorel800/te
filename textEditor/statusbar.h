#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <string>
#include <ncursesw/ncurses.h>

int status_load(const std::string& filename, const std::string& status, const std::string& version, int maxx);

#endif
