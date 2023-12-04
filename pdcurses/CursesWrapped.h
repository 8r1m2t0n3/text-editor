#include "curses.h"

class CursesWrapper {
private:
	WINDOW* stdscr;
public:
	WINDOW* _initscr();
	WINDOW* _newwin(int height, int width, int posY, int posX);
	WINDOW* _resize_window(WINDOW* window, int H, int W);
	int _noecho();
	int _nodelay(WINDOW* window, bool state);
	int _keypad(WINDOW* window, bool state);
	int _resize_term(int y, int x);
	int _getcury(WINDOW* window);
	int _getcurx(WINDOW* window);
	int _getmaxy();
	int _getmaxx();
	int _getmaxy(WINDOW* window);
	int _getmaxx(WINDOW* window);
	int _box(WINDOW*, chtype, chtype);
	int _wattron(WINDOW* window, chtype type);
	int _wattroff(WINDOW* window, chtype type);
	int _wrefresh(WINDOW* window);
	int _refresh();
	int _mvwprintw(WINDOW* window, int yPos, int xPos, const char* str);
	int _waddstr(WINDOW* window, const char* str);
	int _mvwaddstr(WINDOW* window, int yPos, int xPos, const char* str);
	int _waddch(WINDOW* window, char drawChar);
	int _wmove(WINDOW* window, int yPos, int xPos);
	int _move(int yPos, int xPos);
	int _wgetch(WINDOW* window);
	int _mvwin(WINDOW* window, int yPos, int xPos);
	int _wclear(WINDOW* window);
	int _endwin();
	int _nc_getmouse(MEVENT* event);
	mmask_t _mousemask(mmask_t, mmask_t*);
	WINDOW* _get_win();
};

