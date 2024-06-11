#ifndef MODEL_H
#define MODEL_H

#include "my_string/include/my-string.h"
#include <vector>

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

#endif