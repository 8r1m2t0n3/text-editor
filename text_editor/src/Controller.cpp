#include "text_editor/include/MVC.h"

Controller::Controller(Model& model, View& view) {
	this->model = model;
	this->view = view;
}

void Controller::run() {
	view.init_window();
NEW_FILE:
	model.reset_all();
	view.reset_all();
	view.print_main_menu();
	model.calculate_cur_x();
	model.calculate_cur_y();
	model.save_cur_x();
	model.save_cur_y();
	while (1) {
		while (1) {
			pair<int, int> input_event = model.catch_key_event();
			pair<bool, MyString> path_info;
			switch (input_event.first) {

			case ARROWS:

				switch (input_event.second) {
				case LEFT:
					model.decrement_cur_x();
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					break;

				case RIGHT:
					model.increment_cur_x();
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					break;
				}
				break;

			case KEY:

				switch (input_event.second) {
				case BACKSPACE:
					model.decrement_cur_x();
					view.delete_char_from_cur_pos_of_cmd_line(model.get_cur_x(), model.get_cur_y(), PATH_LINE_LEFT_X);
					view.print_cmd_line(model.get_cur_x(), model.get_cur_y(), PATH_LINE_LEFT_X, LOWER_RIGHT_CORNER_X);
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					break;

				case ENTER:
					path_info = model.is_path_valid(view.get_cmd_line());
					if (path_info.first == TRUE) {
						model.set_path(path_info.second);
						view.clean_cmd_line();
						view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), PATH_LINE_LEFT_X, LOWER_RIGHT_CORNER_X);
						goto NEXT;
					}
					else {
						view.clean_cmd_line();
						view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), PATH_LINE_LEFT_X, LOWER_RIGHT_CORNER_X);
						model.set_cur_x(PATH_LINE_LEFT_X);
						model.set_cur_y(CMD_LINE_Y);
						view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					}
					break;

				default: // letters keys
					model.increment_cur_x();
					view.insert_char_in_cur_pos_of_cmd_line(input_event.second, model.get_cur_x(), model.get_cur_y(), PATH_LINE_LEFT_X);
					view.print_cmd_line(model.get_cur_x(), model.get_cur_y(), PATH_LINE_LEFT_X, LOWER_RIGHT_CORNER_X);
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					break;
				}
				break;
			}
		}

	NEXT:
		view.print_wrt_mode_menu();
		model.set_mode(WRT_MODE);
		model.open_file();
		model.save_text_from_file();
		view.print_file_path(model.get_path());
		view.line_up_text(model.get_text());
		print_text_on_cur_page();
		view.upload_terminal();
		while (1) {
			model.save_cur_x();
			model.save_cur_y();
			pair<int, int> input_event = model.catch_key_or_mouse_event();
			int flag = 0;
			int flag1 = 0;
			switch (input_event.first) {
			case MOUSE:
				if (is_cursor_on_cmd_line()) {
					model.set_cur_x(CMD_LINE_LEFT_X);
					model.set_cur_y(CMD_LINE_Y);
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					cmd_line_input();
					model.set_on_text_flag(0);
				}
				else if (is_time_to_save_file()) {
					view.select_save();
					view.upload_terminal();
					model.set_cur_x(model.get_save_x());
					model.set_cur_y(model.get_save_y());
					model.print_in_file();
					Sleep(70);
					view.anselect_save();
					view.upload_terminal();
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
				}
				else if (is_time_to_close_file()) {
					view.select_close();
					view.upload_terminal();
					Sleep(70);
					model.close_file();
					view.clean_screen();
					view.clean_cmd_line();
					view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), PATH_LINE_LEFT_X, LOWER_RIGHT_CORNER_X);
					view.upload_terminal();
					goto NEW_FILE;
				}
				else if (is_fnd_selected()) {
					view.print_fnd_mode_menu();
					view.print_file_path(model.get_path());
					model.set_cur_x(model.get_save_x());
					model.set_cur_y(model.get_save_y());
					view.upload_terminal();
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					model.set_mode(FND_MODE);
				}
				else if (is_nav_selected()) {
					view.print_nav_mode_menu();
					view.print_file_path(model.get_path());
					model.set_cur_x(model.get_save_x());
					model.set_cur_y(model.get_save_y());
					view.upload_terminal();
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					model.set_mode(NAV_MODE);
				}
				else if (is_wrt_selected()) {
					view.print_wrt_mode_menu();
					view.print_file_path(model.get_path());
					model.set_cur_x(model.get_save_x());
					model.set_cur_y(model.get_save_y());
					view.upload_terminal();
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					model.set_mode(WRT_MODE);
				}
				else {
					if (!model.get_on_text_flag()) {
						model.set_cur_x(model.get_save_x());
						model.set_cur_y(model.get_save_y());
						model.set_on_text_flag(1);
					}
					else {
						model.set_cur_x(model.get_save_x());
						model.set_cur_y(model.get_save_y());
					}
				}
				break;

			case ARROWS:

				switch (input_event.second) {
				case UP:
					if (!(model.get_cur_y() == UPPER_LEFT_CORNER_Y && view.get_cur_page() == 0)) {
						if (is_time_to_page_up()) {
							view.decrement_cur_page();
							view.clean_screen();
							print_text_on_cur_page();
							model.set_cur_x(UPPER_LEFT_CORNER_X);
							model.set_cur_y(UPPER_LEFT_CORNER_Y);
						}
						else {
							model.set_cur_x(UPPER_LEFT_CORNER_X);
							model.decrement_cur_y();
						}
					}
					view.print_pos_info(transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()));
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					break;

				case DOWN:
					if (view.get_cur_page() != view.get_pages_cnt() - 1 || (view.get_cur_page() == view.get_pages_cnt() - 1 && model.get_cur_y() != view.get_last_y_coord() - 1)) {
						if (is_time_to_page_down()) {
							view.increment_cur_page();
							view.clean_screen();
							print_text_on_cur_page();
							model.set_cur_x(UPPER_LEFT_CORNER_X);
							model.set_cur_y(UPPER_LEFT_CORNER_Y);
						}
						else {
							model.set_cur_x(UPPER_LEFT_CORNER_X);
							model.increment_cur_y();
						}
						view.print_pos_info(transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()));
						view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					}
					break;

				case LEFT:
					if (model.get_cur_x() == UPPER_LEFT_CORNER_X && 
						model.get_cur_y() == UPPER_LEFT_CORNER_Y && 
						view.get_cur_page() == 0) break;

					if (model.get_cur_x() == UPPER_LEFT_CORNER_X &&
						model.get_cur_y() != UPPER_LEFT_CORNER_Y) {
						place_cursor_on_end_of_prev_line_on_term(model.get_cur_y());
					}

					else if (model.get_cur_x() == UPPER_LEFT_CORNER_X && 
						model.get_cur_y() == UPPER_LEFT_CORNER_Y && 
						view.get_cur_page() != view.get_pages_cnt()) {

						if (transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()).second != 
							transfer_term_coord_to_text_coord(model.get_cur_x(), view.get_term_size().second - 4, view.get_cur_page() - 1).second)
							break;
						view.decrement_cur_page();
						view.clean_screen();
						print_text_on_cur_page();
						model.set_cur_x(LOWER_RIGHT_CORNER_X - 1);
						model.set_cur_y(LOWER_RIGHT_CORNER_Y);
					}
					else model.decrement_cur_x();
					
					view.print_pos_info(transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()));
					view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					break;

				case RIGHT:
					if (!is_last_pos_in_line()) {
						if (model.get_cur_x() == UPPER_RIGHT_CORNER_X - 1 && model.get_cur_y() != LOWER_LEFT_CORNER_Y) {
							place_cursor_on_start_of_next_line_on_term(model.get_cur_y());
							view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
						}
						else if (model.get_cur_x() == LOWER_RIGHT_CORNER_X - 1 && model.get_cur_y() == LOWER_RIGHT_CORNER_Y && view.get_cur_page() != view.get_pages_cnt()) {
							view.increment_cur_page();
							view.clean_screen();
							print_text_on_cur_page();
							model.set_cur_x(1);
							model.set_cur_y(1);
						}
						else model.increment_cur_x();

						view.print_pos_info(transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()));
						view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					}
					break;
				}
				break;

			case KEY:

				switch (input_event.second) {
				case BACKSPACE:
					if (model.get_mode() == WRT_MODE) {
						if (model.get_cur_x() == UPPER_LEFT_CORNER_X && 
							model.get_cur_y() == UPPER_LEFT_CORNER_Y && 
							view.get_cur_page() == 0) break;

						if (model.get_cur_x() == UPPER_LEFT_CORNER_X && model.get_cur_y() != UPPER_LEFT_CORNER_Y) {
							pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page());
							
							if (model.get_cur_x() == UPPER_LEFT_CORNER_X) {
							
								if (transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()).second != transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y() - 1, view.get_cur_page()).second) {
									place_cursor_on_end_of_prev_line_on_term(model.get_cur_y());
									pos = transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page());
									model.add_prev_line_to_cur_line(pos.second);
									view.clean_screen();
									view.line_up_text(model.get_text());
									print_text_on_cur_page();
									model.set_cur_x(model.get_save_x());
									model.set_cur_y(model.get_save_y());
								}
								else {
									model.delete_char_from_cur_pos(pos.first, pos.second);
									place_cursor_on_end_of_prev_line_on_term(model.get_cur_y());
									view.clean_screen();
									view.line_up_text(model.get_text());
									print_text_on_cur_page();
									model.set_cur_x(LOWER_RIGHT_CORNER_X);
									model.set_cur_y(model.get_save_y());
									model.decrement_cur_x();
								}
							}
							else {
								place_cursor_on_end_of_prev_line_on_term(model.get_cur_y());
								model.delete_char_from_cur_pos(pos.first, pos.second);
								view.clean_screen();
								view.line_up_text(model.get_text());
								print_text_on_cur_page();
								model.set_cur_x(LOWER_RIGHT_CORNER_X);
								model.set_cur_y(model.get_save_y());
								model.decrement_cur_x();
							}
						}
						else if (model.get_cur_x() == UPPER_LEFT_CORNER_X && 
							model.get_cur_y() == UPPER_LEFT_CORNER_Y && 
							view.get_cur_page() != view.get_pages_cnt()) {
							if (transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()).second != transfer_term_coord_to_text_coord(model.get_cur_x(), LOWER_LEFT_CORNER_Y, view.get_cur_page() - 1).second) {
								break;
								///*view.decrement_cur_page();
								//model.set_cur_y(LOWER_RIGHT_CORNER_Y);
								//place_cursor_on_end_of_prev_line_on_term(model.get_cur_y());
								//pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page());
								//model.add_prev_line_to_cur_line(pos.second);
								//view.clean_screen();
								//view.line_up_text(model.get_text());
								//print_text_on_cur_page();
								//model.set_cur_x(model.get_save_x());
								//model.set_cur_y(model.get_save_y());*/
							}
							//pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page());
							//model.delete_char_from_cur_pos(pos.first, pos.second);
							//view.decrement_cur_page();
							//view.clean_screen();
							//view.line_up_text(model.get_text());
							//print_text_on_cur_page();
							//model.set_cur_x(LOWER_RIGHT_CORNER_X - 1);
							//model.set_cur_y(LOWER_RIGHT_CORNER_Y);
						}
						else {
							pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page());
							model.delete_char_from_cur_pos(pos.first, pos.second);
							view.clean_screen();
							view.line_up_text(model.get_text());
							print_text_on_cur_page();
							model.set_cur_x(model.get_save_x() - 1);
							model.set_cur_y(model.get_save_y());
						}
						//view.print_pos_info(transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()));
						view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					}
					break;

				case ENTER:
					if (model.get_mode() == WRT_MODE) {
						if (is_time_to_page_down()) {
							if (view.get_cur_page() == view.get_pages_cnt() - 1 && model.get_cur_y() == LOWER_LEFT_CORNER_Y) {
								flag1++;
							}
							else {
								view.increment_cur_page();
								model.set_cur_x(UPPER_LEFT_CORNER_X);
								model.set_cur_y(UPPER_LEFT_CORNER_Y);
							}
						}
						add_line_in_text_next_pos();
						view.line_up_text(model.get_text());
						view.clean_screen();

						if (flag1) {
							view.increment_cur_page();
							print_text_on_cur_page();
							model.set_cur_x(UPPER_LEFT_CORNER_X);
							model.set_cur_y(UPPER_LEFT_CORNER_Y);
							flag1 = 0;
						}
						else {
							print_text_on_cur_page();
							model.set_cur_y(model.get_save_y() + 1);
							model.set_cur_x(UPPER_LEFT_CORNER_X);
						}
						view.print_pos_info(transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()));
						view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					}
					break;

				default: // letters keys
					if (model.get_mode() == WRT_MODE) {
						if (model.get_cur_x() == LOWER_RIGHT_CORNER_X - 1 && model.get_cur_y() == LOWER_RIGHT_CORNER_Y && view.get_cur_page() != view.get_pages_cnt()) {
							if (is_last_pos_in_line()) {
								insert_char_in_cur_pos(input_event.second);
							}
							insert_char_in_cur_pos(input_event.second);
							view.increment_cur_page();
							view.clean_screen();
							print_text_on_cur_page();
							model.set_save_x(1);
							model.set_save_y(1);
							view.upload_terminal();
							flag++;
							goto NEW_PAGE;
						}
						insert_char_in_cur_pos(input_event.second);
					NEW_PAGE:
						view.line_up_text(model.get_text());
						view.clean_screen();
						print_text_on_cur_page();
						model.set_cur_y(model.get_save_y());
						model.set_cur_x(model.get_save_x());
						if (model.get_cur_x() == UPPER_RIGHT_CORNER_X - 1) {
							model.set_cur_y(model.get_save_y() + 1);
							model.set_cur_x(UPPER_LEFT_CORNER_X);
						}
						else {
							if (!flag) {
								model.increment_cur_x();
								flag = 0;
							}
						}
						view.line_up_text(model.get_text());
						view.print_pos_info(transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()));
						view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					}
					break;
				}
				break;
			}
		}
		view.deinit_window();
	}
}

void Controller::cmd_line_input() {
	while (1) {
		pair<int, int> input_event = model.catch_key_or_mouse_event();
		pair<bool, MyString> path_info;
		switch (input_event.first) {
		case MOUSE:
			if (is_cursor_on_text()) {
				model.set_on_text_flag(1);
				model.set_cur_x(model.get_save_x());
				model.set_cur_y(model.get_save_y());
				view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
				return;
			}
			break;

		case ARROWS:

			switch (input_event.second) {
			case LEFT:
				model.decrement_cur_x();
				view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
				break;

			case RIGHT:
				model.increment_cur_x();
				view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
				break;
			}
			break;

		case KEY:

			switch (input_event.second) {
			case BACKSPACE:
				model.decrement_cur_x();
				view.delete_char_from_cur_pos_of_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X);
				view.print_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
				view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
				break;

			case ENTER:
				switch (model.get_mode()) {
				case WRT_MODE:
					if (1) {
						view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
						view.clean_cmd_line();
						model.set_cur_x(model.get_save_x());
						model.set_cur_y(model.get_save_y());
						view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
					}
					break;

				case NAV_MODE:
					if (1) {
						vector<MyString> words = model.words_in_string(view.get_cmd_line());
						if (words.size() == 1) {
							if (words[0] == "^") {
								pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_save_x(), model.get_save_y(), view.get_cur_page());
								pair<pair<int, int>, int> coord = transfer_text_coord_to_term_coord(0, pos.second);
								view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
								view.clean_cmd_line();
								view.set_cur_page(coord.second);
								model.set_cur_x(coord.first.first);
								model.set_cur_y(coord.first.second);
								view.line_up_text(model.get_text());
								view.clean_screen();
								print_text_on_cur_page();
								model.set_cur_x(coord.first.first);
								model.set_cur_y(coord.first.second);
								view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
								return;
							}
							else if (words[0] == "$") {
								pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_save_x(), model.get_save_y(), view.get_cur_page());
								pair<pair<int, int>, int> coord = transfer_text_coord_to_term_coord(model.get_line_length(pos.second) - 1, pos.second);
								view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
								view.clean_cmd_line();
								view.set_cur_page(coord.second);
								model.set_cur_x(coord.first.first);
								model.set_cur_y(coord.first.second);
								view.line_up_text(model.get_text());
								view.clean_screen();
								print_text_on_cur_page();
								model.set_cur_x(coord.first.first);
								model.set_cur_y(coord.first.second);
								view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
								return;
							}
							else if (words[0] == "diw") {
								delete_word_on_cur_pos();
								view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
								view.clean_cmd_line();
								model.set_cur_x(model.get_save_x());
								model.set_cur_y(model.get_save_y());
								view.line_up_text(model.get_text());
								view.clean_screen();
								print_text_on_cur_page();
								model.set_cur_x(model.get_save_x());
								model.set_cur_y(model.get_save_y());
								view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
								return;
							}
							else if (words[0] == "yw") {
								pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_save_x(), model.get_save_y(), view.get_cur_page());
								model.save_word_in_buffer_from_pos(pos.first, pos.second);
								view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
								view.clean_cmd_line();
								model.set_cur_x(model.get_save_x());
								model.set_cur_y(model.get_save_y());
								view.clean_screen();
								print_text_on_cur_page();
								model.set_cur_x(model.get_save_x());
								model.set_cur_y(model.get_save_y());
								view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
								return;
							}
							else if (words[0] == "y") {
								pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_save_x(), model.get_save_y(), view.get_cur_page());
								model.save_line_in_buffer_from_pos(pos.second);
								view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
								view.clean_cmd_line();
								model.set_cur_x(model.get_save_x());
								model.set_cur_y(model.get_save_y());
								view.clean_screen();
								print_text_on_cur_page();
								model.set_cur_x(model.get_save_x());
								model.set_cur_y(model.get_save_y());
								view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
								return;
							}
							else if (words[0] == "p") {
								pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_save_x(), model.get_save_y(), view.get_cur_page());
								model.add_str_to_text_on_pos(model.get_buffer(), pos.first, pos.second);
								view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
								view.clean_cmd_line();
								model.set_cur_x(model.get_save_x());
								model.set_cur_y(model.get_save_y());
								view.line_up_text(model.get_text());
								view.clean_screen();
								print_text_on_cur_page();
								model.set_cur_x(model.get_save_x());
								model.set_cur_y(model.get_save_y());
								view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
								return;
							}
						}
						view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
						view.clean_cmd_line();
						return;
					}
					break;

				case FND_MODE:
					if (1) {
						pair<int, int> pos = model.find_substr_in_text(view.get_cmd_line());
						if (pos.first != -1) {
							pair<pair<int, int>, int> coord = transfer_text_coord_to_term_coord(pos.first, pos.second);

							view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
							view.clean_cmd_line();

							model.set_on_text_flag(1);

							view.set_cur_page(coord.second);
							model.set_cur_x(coord.first.first);
							model.set_cur_y(coord.first.second);
							model.save_cur_x();
							model.save_cur_y();

							view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
							return;
						}
						else {
							view.paint_off_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
							view.clean_cmd_line();
							model.set_cur_x(model.get_save_x());
							model.set_cur_y(model.get_save_y());
							view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
						}
					}
					break;
				}
				break;

			default: // letters keys
				model.increment_cur_x();
				view.insert_char_in_cur_pos_of_cmd_line(input_event.second, model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X);
				view.print_cmd_line(model.get_cur_x(), model.get_cur_y(), CMD_LINE_LEFT_X, CMD_LINE_RIGHT_X);
				view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
				break;
			}
			break;
		}
	}
}

bool Controller::is_cursor_on_cmd_line() {
	return (model.get_cur_x() >= CMD_LINE_LEFT_X && 
		model.get_cur_x() < CMD_LINE_RIGHT_X && 
		model.get_cur_y() == CMD_LINE_Y);
}

bool Controller::is_cursor_on_text() {
	return !is_cursor_on_cmd_line();
}

bool Controller::is_time_to_close_file() {
	int cur_x = model.get_cur_x();
	int cur_y = model.get_cur_y();
	if (cur_y == CMD_LINE_Y && (
		cur_x > LOWER_RIGHT_CORNER_X - 8 && 
		cur_x < LOWER_RIGHT_CORNER_X))
		return 1;
	return 0;
}

bool Controller::is_time_to_save_file() {
	if (model.get_cur_y() == CMD_LINE_Y && (
		model.get_cur_x() > LOWER_RIGHT_CORNER_X - 15 && 
		model.get_cur_x() < LOWER_RIGHT_CORNER_X - 8))
		return 1;
	return 0;
}

void Controller::print_text_on_cur_page() {
	model.save_cur_x();
	model.save_cur_y();
	int cur_page = view.get_cur_page();

	vector<pair<int, pair<pair<int, int>, pair<int, int>>>> coord_in_text = view.get_text_line_up();

	int text_top_chr = coord_in_text[cur_page].second.first.first;
	int text_top_line = coord_in_text[cur_page].second.first.second;

	int text_last_chr = coord_in_text[cur_page].second.second.first;
	int text_last_line = coord_in_text[cur_page].second.second.second;

	int line_cnt = model.get_lines_cnt();

	model.set_cur_x(UPPER_LEFT_CORNER_X);
	model.set_cur_y(UPPER_LEFT_CORNER_Y);
	view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());

	int i = text_top_chr;

	int cur_line_num = text_top_line;

	MyString cur_line = model.get_line(cur_line_num);

	while (1) {
		int cur_line_size = cur_line.size();
		while (i != cur_line_size) {
			char chr = cur_line[i];

			if (model.get_cur_x() == LOWER_RIGHT_CORNER_X && 
				model.get_cur_y() == LOWER_RIGHT_CORNER_Y || 
				model.get_cur_y() > LOWER_RIGHT_CORNER_Y)
				break;

			if (model.get_cur_x() == UPPER_RIGHT_CORNER_X) {
				model.set_cur_x(UPPER_LEFT_CORNER_X);
				model.increment_cur_y();
				view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
				view.print_char_in_cur_pos(chr);
				model.increment_cur_x();
			}
			else {
				view.print_char_in_cur_pos(chr);
				model.increment_cur_x();
				view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
			}
			i++;
		}
		model.increment_cur_y();
		model.set_cur_x(UPPER_LEFT_CORNER_X);
		view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
		view.upload_terminal();
		cur_line_num++;

		if (cur_line_num == line_cnt) break;
		cur_line = model.get_line(cur_line_num);
		i = 0;

		if (cur_line_num - 1 == text_last_line) break;
	}
	view.set_last_y_coord(model.get_cur_y());
	model.set_cur_x(UPPER_LEFT_CORNER_X);
	model.set_cur_y(UPPER_LEFT_CORNER_Y);
	view.move_cursor_in_cur_pos(model.get_cur_x(), model.get_cur_y());
	view.upload_terminal();
}

bool Controller::is_time_to_page_down() {
	if (model.get_cur_y() == LOWER_LEFT_CORNER_Y) return 1;
	return 0;
}

bool Controller::is_time_to_page_up() {
	if (model.get_cur_y() == UPPER_LEFT_CORNER_Y) return 1;
	return 0;
}

bool Controller::is_fnd_selected() {
	if (model.get_cur_x() >= view.get_term_size().first - 21 && 
		model.get_cur_x() <= view.get_term_size().first - 17 && 
		model.get_cur_y() == CMD_LINE_Y) return 1;
	return 0;
}

bool Controller::is_nav_selected() {
	if (model.get_cur_x() >= view.get_term_size().first - 27 && 
		model.get_cur_x() <= view.get_term_size().first - 23 && 
		model.get_cur_y() == CMD_LINE_Y) return 1;
	return 0;
}

bool Controller::is_wrt_selected() {
	if (model.get_cur_x() >= view.get_term_size().first - 33 && 
		model.get_cur_x() <= view.get_term_size().first - 29 && 
		model.get_cur_y() == CMD_LINE_Y) return 1;
	return 0;
}

bool Controller::is_last_pos_in_line() {
	pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page());
	int line_len = model.get_line_length(pos.second);
	int x_pos_in_line = pos.first + 1;
	if (x_pos_in_line == line_len - 1) return 1;
	return 0;
}


pair<int, int> Controller::transfer_term_coord_to_text_coord(int xTerm, int yTerm, int page) {
	vector<MyString> text = model.get_text();
	const int line_cnt = model.get_lines_cnt();

	int line_num = 0;

	int term_x = 1;
	int term_y = 1;
	int term_page = 0;

	int text_x = 0;
	int text_y = 0;

	while (1) {
		MyString line = model.get_line(line_num);
		int line_len = line.size();
		while (1) {
			if (term_x == xTerm && term_y == yTerm && term_page == page) {
				pair<int, int> pos;
				pos.first = text_x;
				pos.second = text_y;
				return pos;
			}
			term_x++;
			text_x++;

			if (text_x == line_len) {
				text_x = 0;
				term_x = 1;
				term_y++;
				text_y++;
				if (term_x == LOWER_LEFT_CORNER_X && term_y == LOWER_LEFT_CORNER_Y + 1) {
					term_x = 1;
					term_y = 1;
					term_page++;
				}
				break;
			}
			if (term_x == UPPER_RIGHT_CORNER_X) {
				term_x = 1;
				term_y++;
			}
			if (term_x == LOWER_LEFT_CORNER_X && term_y == LOWER_LEFT_CORNER_Y + 1) {
				term_x = 1;
				term_y = 1;
				term_page++;
			}
		}
		line_num++;
	}
}

pair<pair<int, int>, int> Controller::transfer_text_coord_to_term_coord(int xText, int yText) {
	vector<MyString> text = model.get_text();
	int xTerm = 0;
	int yTerm = 0;
	int page = 0;

	int x = 0;
	int y = 0;

	pair<pair<int, int>, int> coord;

	int line_cnt = model.get_lines_cnt();
	while (y != line_cnt) {
		int cur_line_len = model.get_line_length(y);
		while (x != cur_line_len) {
			if (yTerm == LOWER_LEFT_CORNER_Y) {
				page++;
				xTerm = 0;
				yTerm = 0;
			}
			if (xTerm == UPPER_RIGHT_CORNER_X - 1) {
				xTerm = 0;
				yTerm++;
			}
			if (x == xText && y == yText) {
				coord.first.first = xTerm + 1;
				coord.first.second = yTerm + 1;
				coord.second = page;
				return coord;
			}
			x++;
			xTerm++;
		}
		y++;
		x = 0;
		xTerm = 0;
		yTerm++;
	}
	coord.first.first = -1;
	coord.first.second = -1;
	coord.second = -1;
	return coord;
}

void Controller::place_cursor_on_end_of_prev_line_on_term(int line_num) {
	pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_cur_x(), line_num, view.get_cur_page());
	int line_len = 0;
	if (pos.second != 0) {
		line_len = model.get_line_length(pos.second - 1) - 1;
	}
	else {
		line_len = model.get_line_length(pos.second) - 1;
	}
	if (transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page()).second == 
		transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y() - 1, view.get_cur_page()).second) {
		model.set_cur_x(LOWER_RIGHT_CORNER_X - 1);
		model.set_cur_y(line_num - 1);
	}
	else {
		int ost = line_len % (LOWER_RIGHT_CORNER_X - 1);
		model.set_cur_x(ost);
		model.set_cur_y(line_num - 1);
		model.save_cur_x();
		model.save_cur_y();
	}
}

void Controller::place_cursor_on_start_of_next_line_on_term(int line_num) {
	pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_cur_x(), line_num, view.get_cur_page());
	int line_len = model.get_line_length(pos.second);
	if (line_len > LOWER_RIGHT_CORNER_X - 1) {
		if (transfer_term_coord_to_text_coord(UPPER_LEFT_CORNER_X, line_num + 1, view.get_cur_page()).second == pos.second) {
			model.set_cur_x(UPPER_LEFT_CORNER_X);
			model.set_cur_y(line_num + 1);
		}
	}
}

void Controller::insert_char_in_cur_pos(char chr) {
	pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page());
	model.insert_char_in_cur_pos(chr, pos.first, pos.second);
}

void Controller::add_line_in_text_next_pos() {
	vector<MyString> text = model.get_text();
	pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_cur_x(), model.get_cur_y(), view.get_cur_page());
	model.add_line_in_text(pos.first, pos.second);
}

void Controller::delete_word_on_cur_pos() {
	pair<int, int> pos = transfer_term_coord_to_text_coord(model.get_save_x(), model.get_save_y(), view.get_cur_page());
	model.delete_word_on_pos(pos.first, pos.second);
}
