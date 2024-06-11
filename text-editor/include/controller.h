#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "text-editor/include/model.h"
#include "text-editor/include/view.h"

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
	std::pair<int, int> transfer_term_coord_to_text_coord(int xTerm, int yTerm, int page); // x, y
	std::pair<std::pair<int, int>, int> transfer_text_coord_to_term_coord(int xText, int yText); // x, y, page
	void place_cursor_on_end_of_prev_line_on_term(int line_num);
	void place_cursor_on_start_of_next_line_on_term(int line_num);
	void insert_char_in_cur_pos(char chr);
	void add_line_in_text_next_pos();
	void delete_word_on_cur_pos();
};

#endif