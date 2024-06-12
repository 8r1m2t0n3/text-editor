#ifndef VIEW_H
#define VIEW_H

#include "curses_wrapped.h"
#include "my_string.h"
#include "model.h"

class View {
private:
	Model model;
	WINDOW* mainWindow;
	MyString cmd_line;
	int weidth; // x
	int hight; // y
	int cur_page;
	int pages_cnt;
	std::vector<std::pair<int, std::pair<std::pair<int, int>, std::pair<int, int>>>> mark; // x, y
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
	std::pair<int, int> get_term_size(); // x, y
	void upload_terminal();
	void increment_cur_page();
	void decrement_cur_page();
	void line_up_text(std::vector<MyString> text);
	int get_cur_page();
	int get_pages_cnt();
	void set_cur_page(int page);
	std::vector<std::pair<int, std::pair<std::pair<int, int>, std::pair<int, int>>>> get_text_line_up();
	void clean_screen();
	void print_pos_info(std::pair<int, int> pos);
	int get_last_y_coord();
	void set_last_y_coord(int y);
	void reset_all();
	void print_file_path(MyString path);

private:
	void print_menu();
	MyString num_to_string(int num);
	int digit_in_num(int num);
};

#endif