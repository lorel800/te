#ifndef EDITOR_H
#define EDITOR_H

#include <ncursesw/ncurses.h>
#include <vector>
#include <string>
#include "data.h"

/**
 * @brief Обрабатывает нажатие клавиши, изменяя состояние редактора.
 * * @param ch Код нажатой клавиши.
 * @param locale_data Структура данных редактора.
 * @param lines Вектор строк, содержащий текст.
 * @param cursorY Координата курсора по оси Y.
 * @param cursorX Координата курсора по оси X.
 * @param scrollOffset Смещение прокрутки по вертикали.
 * @return int Возвращает 0, если нужно завершить программу (нажата Escape), иначе 1.
 */
int handle_input(wint_t ch, data& locale_data, std::vector<std::wstring>& lines, int& cursorY, int& cursorX, int& scrollOffset);

#endif // EDITOR_H
