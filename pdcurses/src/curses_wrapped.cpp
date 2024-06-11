#include "pdcurses/include/curses_wrapped.h"

WINDOW* CursesWrapper::_initscr() {
    stdscr = initscr();
    return stdscr;
}

WINDOW* CursesWrapper::_newwin(int height, int width, int posY, int posX) {
    return newwin(height, width, posY, posX);
}

WINDOW* CursesWrapper::_resize_window(WINDOW* window, int H, int W) {
    return resize_window(window, H, W);
}

int CursesWrapper::_noecho() {
    return noecho();
}

int CursesWrapper::_nodelay(WINDOW* window, bool state) {
    return nodelay(window, state);
}

int CursesWrapper::_keypad(WINDOW* window, bool state) {
    return keypad(window, state);
}

int CursesWrapper::_resize_term(int y, int x) {
    return resize_term(y, x);
}

int CursesWrapper::_getcury(WINDOW* window) {
    return getcury(window);
}

int CursesWrapper::_getcurx(WINDOW* window) {
    return getcurx(window);
}

int CursesWrapper::_getmaxy() {
    return _getmaxy(stdscr);
}

int CursesWrapper::_getmaxx() {
    return _getmaxx(stdscr);
}

int CursesWrapper::_getmaxy(WINDOW* window) {
    return getmaxy(window);
}

int CursesWrapper::_getmaxx(WINDOW* window) {
    return getmaxx(window);
}

int CursesWrapper::_box(WINDOW* window, chtype yStart, chtype xStart) {
    return box(window, yStart, xStart);
}

int CursesWrapper::_wattron(WINDOW* window, chtype type) {
    return wattron(window, type);
}

int CursesWrapper::_wattroff(WINDOW* window, chtype type) {
    return wattroff(window, type);
}

int CursesWrapper::_wrefresh(WINDOW* window) {
    return wrefresh(window);
}

int CursesWrapper::_refresh() {
    return _wrefresh(stdscr);
}

int CursesWrapper::_mvwprintw(WINDOW* window, int yPos, int xPos, const char* str) {
    return mvwprintw(window, yPos, xPos, str);
}

int CursesWrapper::_waddstr(WINDOW* window, const char* str) {
    return waddstr(window, str);
}

int CursesWrapper::_mvwaddstr(WINDOW* window, int yPos, int xPos, const char* str) {
    return mvwaddstr(window, yPos, xPos, str);
}

int CursesWrapper::_waddch(WINDOW* window, char drawChar) {
    return waddch(window, drawChar);
}

int CursesWrapper::_wmove(WINDOW* window, int yPos, int xPos) {
    return wmove(window, yPos, xPos);
}

int CursesWrapper::_move(int yPos, int xPos) {
    return move(yPos, xPos);
}

int CursesWrapper::_wgetch(WINDOW* window) {
    return wgetch(window);
}

int CursesWrapper::_mvwin(WINDOW* window, int yPos, int xPos) {
    return mvwin(window, yPos, xPos);
}

int CursesWrapper::_wclear(WINDOW* window) {
    return wclear(window);
}

int CursesWrapper::_endwin() {
    return endwin();
}

int CursesWrapper::_nc_getmouse(MEVENT* event) {
    return nc_getmouse(event);
}

mmask_t CursesWrapper::_mousemask(mmask_t mask1, mmask_t* mask2) {
    return  mousemask(mask1, mask2);
}
