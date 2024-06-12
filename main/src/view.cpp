#include "view.h"
#include "editor_constants.h"
#include <windows.h>
#include <cmath>
using namespace std;

extern CursesWrapper _curses_funcs;
extern WINDOW* _textEditor;

void View::init_window() {
	_curses_funcs._initscr();

	_curses_funcs._resize_term(24, 80);

	hight = _curses_funcs._getmaxy();
	weidth = _curses_funcs._getmaxx();

	mainWindow = _curses_funcs._newwin(hight, weidth, 0, 0);
	_curses_funcs._noecho();
	_curses_funcs._nodelay(mainWindow, TRUE);
	_curses_funcs._keypad(mainWindow, TRUE);
	_curses_funcs._box(mainWindow, '|', '=');

	pages_cnt = cur_page = 0;

	_curses_funcs._mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	_textEditor = mainWindow;
}

void View::deinit_window() {
	_curses_funcs._endwin();
}

void View::move_cursor_in_cur_pos(int xCur, int yCur) {
	_curses_funcs._wmove(mainWindow, yCur, xCur);
}

void View::add_char_to_cmd_line(char chr) {
	cmd_line.append(1, chr);
}

MyString View::get_cmd_line() {
	return cmd_line;
}

void View::delete_char_from_cur_pos_of_cmd_line(int xCur, int yCur, int fst_pos) {
	cmd_line.erase(xCur - fst_pos, 1);
	_curses_funcs._waddch(mainWindow, ' ');
}

void View::print_char_in_cur_pos(char chr) {
	_curses_funcs._waddch(mainWindow, chr);
}

void View::insert_char_in_cur_pos_of_cmd_line(char chr, int xCur, int yCur, int fst_pos) {
	if (cmd_line.size() != 0)
		cmd_line.insert(xCur - (fst_pos + 1), 1, chr);
	else cmd_line.append(1, chr);
}

void View::print_cmd_line(int xCur, int yCur, int fst_pos, int last_pos) {
	paint_off_cmd_line(xCur, yCur, fst_pos, last_pos);
	_curses_funcs._mvwprintw(mainWindow, yCur, fst_pos, cmd_line.c_str());
}

void View::paint_off_cmd_line(int xCur, int yCur, int fst_pos, int last_pos) {
	for (int i = fst_pos; i < last_pos; i++) {
		move_cursor_in_cur_pos(i, yCur);
		_curses_funcs._waddch(mainWindow, ' ');
	}
}

void View::clean_cmd_line() {
	cmd_line.clear();
}

void View::print_main_menu() {
	_curses_funcs._box(mainWindow, '|', '=');

	int len = 1;
	while (len != weidth - 1) {
		_curses_funcs._mvwprintw(mainWindow, hight - 3, len, "=");
		len++;
	}
	_curses_funcs._mvwprintw(mainWindow, hight - 2, 1, PATH);

	_curses_funcs._wmove(mainWindow, hight - 2, 6);
}

void View::print_nav_mode_menu() {
	print_menu();
	select_nav();
}

void View::print_fnd_mode_menu() {
	print_menu();
	select_fnd();
}

void View::print_wrt_mode_menu() {
	print_menu();
	select_wrt();
}

void View::print_menu() {
	_curses_funcs._box(mainWindow, '|', '=');

	int len = 1;
	while (len != weidth - 1) {
		_curses_funcs._mvwprintw(mainWindow, hight - 3, len, "=");
		len++;
	}

	MyString str("|| WRT | NAW | FND || SAVE | CLOSE ");
	_curses_funcs._mvwprintw(mainWindow, hight - 2, weidth - 36, str.c_str());

	_curses_funcs._mvwprintw(mainWindow, hight - 2, 1, CMD);
	_curses_funcs._mvwprintw(mainWindow, hight - 1, weidth - sizeof(LINE) - 1, COL"0");
	_curses_funcs._mvwprintw(mainWindow, hight - 1, weidth - sizeof(LINE) - sizeof(COL) - 3, LINE"0");
	_curses_funcs._mvwprintw(mainWindow, hight - 1, weidth - sizeof(LINE) - sizeof(COL) - sizeof(PAGE) - 4, PAGE"0");
}

void View::select_fnd() {
	_curses_funcs._wattron(mainWindow, A_STANDOUT);
	_curses_funcs._mvwprintw(mainWindow, hight - 2, weidth - 22, " FND ");
	_curses_funcs._wattroff(mainWindow, A_STANDOUT);
}


void View::select_nav() {
	_curses_funcs._wattron(mainWindow, A_STANDOUT);
	_curses_funcs._mvwprintw(mainWindow, hight - 2, weidth - 28, " NAW ");
	_curses_funcs._wattroff(mainWindow, A_STANDOUT);
}

void View::select_wrt() {
	_curses_funcs._wattron(mainWindow, A_STANDOUT);
	_curses_funcs._mvwprintw(mainWindow, hight - 2, weidth - 34, " WRT ");
	_curses_funcs._wattroff(mainWindow, A_STANDOUT);
}

void View::select_save() {
	_curses_funcs._wattron(mainWindow, A_STANDOUT);
	_curses_funcs._mvwprintw(mainWindow, hight - 2, weidth - 15, " SAVE ");
	_curses_funcs._wattroff(mainWindow, A_STANDOUT);
}

void View::select_close() {
	_curses_funcs._wattron(mainWindow, A_STANDOUT);
	_curses_funcs._mvwprintw(mainWindow, hight - 2, weidth - 8, " CLOSE ");
	_curses_funcs._wattroff(mainWindow, A_STANDOUT);
}

void View::anselect_save() {
	_curses_funcs._mvwprintw(mainWindow, hight - 2, weidth - 15, " SAVE ");
}

void View::anselect_close() {
	_curses_funcs._mvwprintw(mainWindow, hight - 2, weidth - 10, " CLOSE ");
}

pair<int, int> View::get_term_size() {
	pair<int, int> size;
	size.first = weidth;
	size.second = hight;
	return size;
}

void View::upload_terminal() {
	_curses_funcs._refresh();
	_curses_funcs._wrefresh(mainWindow);
}

void View::increment_cur_page() {
	cur_page++;
}

void View::decrement_cur_page() {
	cur_page--;
}

void View::line_up_text(vector<MyString> text) {
	if (!mark.empty()) {
		int size = mark.size();
		for (int i = 0; i < size; i++) {
			mark.pop_back();
		}
	}
	int chr_cnt = 0;
	const int max_chr_cnt = (weidth - 2) * (hight - 4);

	int chr_from_line_on_page = 0;

	const int line_cnt = text.size();

	int page_cnt = 0;

	pair<int, int> fst_pos;
	fst_pos.first = 0;
	fst_pos.second = 0;

	int cur_line = 0, cur_chr = 0;

	pair<int, int> snd_pos;
	bool flag = 0;
	int cur_line_len = 0;
	for (cur_line = 0; cur_line < line_cnt; cur_line++) {
		cur_line_len = text[cur_line].size();
		for (cur_chr = 0; cur_chr <= cur_line_len; cur_chr++, chr_cnt++, chr_from_line_on_page++) {
			if (chr_cnt == max_chr_cnt) {
				chr_cnt = 0;

				pair<pair<int, int>, pair<int, int>> pos;
				pos.first = fst_pos;
				pos.second = snd_pos;

				pair<int, pair<pair<int, int>, pair<int, int>>> mrk;
				mrk.first = page_cnt;
				mrk.second = pos;

				mark.push_back(mrk);

				page_cnt++;
				flag = 0;
			}
			int ost = chr_from_line_on_page % (weidth - 2);
			if (chr_cnt + (weidth - 2) - ost == max_chr_cnt) {
				snd_pos.first = cur_chr;
				snd_pos.second = cur_line;
			}
			if (chr_from_line_on_page == cur_line_len) {
				chr_cnt += (weidth - 2) - ost - 1;
				chr_from_line_on_page = -1;
			}
			if (flag == 0 && page_cnt != 0) {
				fst_pos.first = cur_chr;
				fst_pos.second = cur_line;
				flag++;
			}
		}
	}
	snd_pos.first = cur_line_len - 1;
	snd_pos.second = line_cnt;
	pair<pair<int, int>, pair<int, int>> pos;
	pos.first = fst_pos;
	pos.second = snd_pos;

	pair<int, pair<pair<int, int>, pair<int, int>>> mrk;
	mrk.first = page_cnt;
	mrk.second = pos;

	mark.push_back(mrk);

	page_cnt++;
	pages_cnt = page_cnt;
}

int View::get_cur_page() {
	return cur_page;
}

int View::get_pages_cnt() {
	return pages_cnt;
}

void View::set_cur_page(int page) {
	cur_page = page;
}

vector<pair<int, pair<pair<int, int>, pair<int, int>>>> View::get_text_line_up() {
	return mark;
}

void View::clean_screen() {
	for (int j = 1; j < hight - 3; j++) {
		for (int i = 1; i < weidth - 1; i++) {
			_curses_funcs._wmove(mainWindow, j, i);
			print_char_in_cur_pos(' ');
		}
	}
	upload_terminal();
}

void View::print_pos_info(pair<int, int> pos) {
	int xCur = pos.first + 1;
	int yCur = pos.second + 1;

	int len = 1;
	while (len != weidth - 1) {
		_curses_funcs._mvwprintw(mainWindow, hight - 1, len, "=");
		len++;
	}
	MyString str(PAGE);
	str += num_to_string(cur_page + 1);
	str.append(1, '=');
	str += COL;
	str += num_to_string(xCur);
	str.append(1, '=');
	str += LINE;
	str += num_to_string(yCur);
	_curses_funcs._mvwprintw(mainWindow, hight - 1, 1, str.c_str());
}

MyString View::num_to_string(int num) {
	int ost;;
	int i = 0;
	char arr[10];
	while (num > 0) {
		ost = num % 10;
		num /= 10;
		arr[i] = ost + 48;
		i++;
	}
	arr[i] = '\0';
	char arr2[10];
	i--;
	int j = 0;
	for (; i >= 0; j++, i--) {
		arr2[j] = arr[i];
	}
	arr2[j] = '\0';
	MyString str(arr2);
	return str;
}

int View::digit_in_num(int num) {
	return int(log10(num) + 1);
}

int View::get_last_y_coord() {
	return last_y_coord;
}

void View::set_last_y_coord(int y) {
	last_y_coord = y;
}

void View::reset_all() {
	cur_page = 0;
	pages_cnt = 0;
	mark.clear();
	last_y_coord = 0;
}

void View::print_file_path(MyString path) {
	_curses_funcs._mvwprintw(mainWindow, 0, weidth/2-path.size()/2, path.c_str());
}
