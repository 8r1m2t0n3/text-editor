#define _CRT_SECURE_NO_WARNINGS
#include "curses_wrapped.h"
#include "my_string/include/my_string.h"
#include <windows.h>
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

#define PAGE "page:"
#define LINE "line:"
#define COL "col:"
#define CMD "COMMAND:"
#define PATH "PATH:"

#define WRT_MODE 0x935
#define NAV_MODE 0x239
#define FND_MODE 0x368

#define ARROWS 4
#define MOUSE 2
#define KEY 55
#define SPACE 32
#define ESC 27
#define ENTER 10
#define BACKSPACE 8
#define UP 259
#define DOWN 258
#define RIGHT 261
#define LEFT 260

#define UPPER_LEFT_CORNER_X 1 
#define UPPER_LEFT_CORNER_Y 1
#define UPPER_RIGHT_CORNER_X (view.get_term_size().first - 1)
#define UPPER_RIGHT_CORNER_Y 1 
#define LOWER_LEFT_CORNER_X 1
#define LOWER_LEFT_CORNER_Y (view.get_term_size().second - 4)
#define LOWER_RIGHT_CORNER_X (view.get_term_size().first - 1)
#define LOWER_RIGHT_CORNER_Y (view.get_term_size().second - 4)

#define PATH_LINE_LEFT_X 6
#define CMD_LINE_LEFT_X 9
#define CMD_LINE_RIGHT_X (view.get_term_size().first - 36)
#define CMD_LINE_Y (view.get_term_size().second - 2)

class Model {
private:
	int mode;
	int save_x;
	int save_y;
	int cur_x;
	int cur_y;
	MyString path;
	vector<MyString> text;
	bool on_text_flag;
	MyString buffer;
public:
	MyString get_path();
	void set_path(MyString path);
	pair<bool, MyString> is_path_valid(MyString path);
	pair<bool, MyString> is_command_valid(MyString path);
	void save_cur_x();
	void save_cur_y();
	void set_save_x(int xNew);
	void set_save_y(int yNew);
	int get_save_x();
	int get_save_y();
	void calculate_cur_x();
	void calculate_cur_y();
	int get_cur_x();
	int get_cur_y();
	void set_cur_x(int xNew);
	void set_cur_y(int yNew);
	void open_file();
	void close_file();
	void print_in_file();
	void save_text_from_file();
	vector<MyString> get_text();
	pair<int, int> catch_key_event();
	pair<int, int> catch_key_or_mouse_event();
	void increment_cur_x();
	void increment_cur_y();
	void decrement_cur_x();
	void decrement_cur_y();
	int get_lines_cnt();
	MyString get_line(int line_cnt);
	int get_line_length(int num);
	void reset_all();
	void set_on_text_flag(bool flag);
	bool get_on_text_flag();
	void insert_char_in_cur_pos(char chr, int xPos, int yPos);
	void add_line_in_text(int xPos, int yPos);
	void delete_char_from_cur_pos(int xPos, int yPos);
	void add_prev_line_to_cur_line(int cur_line_num);
	void set_mode(int mode);
	int get_mode();
	vector<MyString> words_in_string(MyString str);
	pair<int, int> find_substr_in_text(MyString str); // x, y
	void delete_word_on_pos(int xPos, int yPos);
	void save_word_in_buffer_from_pos(int xPos, int yPos);
	void save_line_in_buffer_from_pos(int yPos);
	MyString get_buffer();
	void add_str_to_text_on_pos(MyString str, int xPos, int yPos);
};

class View {
private:
	Model model;
	WINDOW* mainWindow;
	MyString cmd_line;
	int weidth; // x
	int hight; // y
	int cur_page;
	int pages_cnt;
	vector<pair<int, pair<pair<int, int>, pair<int, int>>>> mark; // x, y
	int last_y_coord;
public:
	void init_window();
	void deinit_window();
	void move_cursor_in_cur_pos(int xCur, int yCur);
	void add_char_to_cmd_line(char chr);
	MyString get_cmd_line();
	void delete_char_from_cur_pos_of_cmd_line(int xCur, int yCur, int fst_pos);
	void print_char_in_cur_pos(char chr);
	void insert_char_in_cur_pos_of_cmd_line(char chr, int xCur, int yCur, int fst_pos);
	void print_cmd_line(int xCur, int yCur, int fst_pos, int last_pos);
	void paint_off_cmd_line(int xCur, int yCur, int fst_pos, int last_pos);
	void clean_cmd_line();
	void print_main_menu();
	void print_nav_mode_menu();
	void print_fnd_mode_menu();
	void print_wrt_mode_menu();
	void select_nav();
	void select_fnd();
	void select_wrt();
	void select_save();
	void select_close();
	void anselect_save();
	void anselect_close();
	pair<int, int> get_term_size(); // x, y
	void upload_terminal();
	void increment_cur_page();
	void decrement_cur_page();
	void line_up_text(vector<MyString> text);
	int get_cur_page();
	int get_pages_cnt();
	void set_cur_page(int page);
	vector<pair<int, pair<pair<int, int>, pair<int, int>>>> get_text_line_up();
	void clean_screen();
	void print_pos_info(pair<int, int> pos);
	int get_last_y_coord();
	void set_last_y_coord(int y);
	void reset_all();
	void print_file_path(MyString path);

private:
	void print_menu();
	MyString num_to_string(int num);
	int digit_in_num(int num);
};

class Controller {
private:
	Model model;
	View view;
public:
	Controller(Model& model, View& view);
	void run();
private:
	void print_text_on_cur_page();
	void cmd_line_input();
	bool is_cursor_on_cmd_line();
	bool is_cursor_on_text();
	bool is_time_to_close_file();
	bool is_time_to_save_file();
	bool is_time_to_page_down();
	bool is_time_to_page_up();
	bool is_fnd_selected();
	bool is_nav_selected();
	bool is_wrt_selected();
	bool is_last_pos_in_line();
	pair<int, int> transfer_term_coord_to_text_coord(int xTerm, int yTerm, int page); // x, y
	pair<pair<int, int>, int> transfer_text_coord_to_term_coord(int xText, int yText); // x, y, page
	void place_cursor_on_end_of_prev_line_on_term(int line_num);
	void place_cursor_on_start_of_next_line_on_term(int line_num);
	void insert_char_in_cur_pos(char chr);
	void add_line_in_text_next_pos();
	void delete_word_on_cur_pos();
};
