#include "text_editor/include/mvc.h"

CursesWrapper _curses_funcs;
WINDOW* _textEditor;
fstream _file;

MyString Model::get_path() {
	return path;
}

void Model::set_path(MyString path) {
	this->path = path;
}

pair<bool, MyString> Model::is_path_valid(MyString path) {
	fstream file;
	file.open(path.c_str());
	pair<bool, MyString> flagAndPath;
	if (!file) {
		flagAndPath.first = false;
		flagAndPath.second.append(1, '\0');
	}
	else {
		flagAndPath.first = true;
		flagAndPath.second = path;
		file.close();
	}
	return flagAndPath;
}

pair<bool, MyString> Model::is_command_valid(MyString path)
{
	return pair<bool, MyString>();
}

void Model::save_cur_x() {
	save_x = cur_x;
}

void Model::save_cur_y() {
	save_y = cur_y;
}

void Model::set_save_x(int xNew) {
	save_x = xNew;
}

void Model::set_save_y(int yNew) {
	save_y = yNew;
}

int Model::get_save_x() {
	return save_x;
}

int Model::get_save_y() {
	return save_y;
}

void Model::calculate_cur_x() {
	cur_x = _curses_funcs._getcurx(_textEditor);
}

void Model::calculate_cur_y() {
	cur_y = _curses_funcs._getcury(_textEditor);
}

int Model::get_cur_x() {
	return cur_x;
}

int Model::get_cur_y() {
	return cur_y;
}

void Model::set_cur_x(int xNew) {
	cur_x = xNew;
}

void Model::set_cur_y(int yNew) {
	cur_y = yNew;
}

void Model::open_file() {
	_file.open(path.c_str());
}

void Model::close_file() {
	_file.close();
}

void Model::print_in_file() {
	close_file();

	std::ofstream ofs;
	ofs.open(path.c_str(), std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	open_file();

	int line_cnt = get_lines_cnt();
	for (int i = 0; i < line_cnt; i++) {
		MyString line = text[i];
		line.erase(text[i].size() - 2, 2);
		line.append(1, '\n');
		_file << line.c_str();
	}
	close_file();
	open_file();
}

void Model::save_text_from_file() {
	text.clear();
	int line_ind = 0;
	while (!_file.eof()) {
		string line;
		getline(_file, line);
		line.append(2, ' ');
		text.push_back(line);
		line_ind++;
	}
}

vector<MyString> Model::get_text() {
	return text;
}

pair<int, int> Model::catch_key_event() {
	int c = _curses_funcs._wgetch(_textEditor);

	pair<int, int> pos;
	if (c == UP || c == DOWN || c == LEFT || c == RIGHT) {
		pos.first = ARROWS;
		pos.second = c;
	}
	else if (c == BACKSPACE) {
		pos.first = KEY;
		pos.second = c;
	}
	else if (c == ENTER) {
		pos.first = KEY;
		pos.second = c;
	}
	else if (c == ESC) {
		pos.first = KEY;
		pos.second = c;
	}
	else if (c == SPACE) {
		pos.first = KEY;
		pos.second = c;
	}
	else if (c != -1 && c != KEY_MOUSE) {
		pos.first = KEY;
		pos.second = c;
	}
	return pos;
}

//pair<int, int> Model::wait_for_mouse_event() {
//	while (1) {
//		int c = _curses_funcs._wgetch(_textEditor);
//
//		pair<int, int> pos;
//		if (c == KEY_MOUSE) {
//			MEVENT event;
//			if (_curses_funcs._nc_getmouse(&event) == OK) {
//				cur_x = event.x;
//				cur_y = event.y;
//				pos.first = MOUSE;
//				pos.second = c;
//				return pos;
//			}
//		}
//	}
//}

pair<int, int> Model::catch_key_or_mouse_event() {
	int c = _curses_funcs._wgetch(_textEditor);

	pair<int, int> pos;
	if (c == KEY_MOUSE) {
		MEVENT event;
		if (_curses_funcs._nc_getmouse(&event) == OK) {
			cur_x = event.x;
			cur_y = event.y;
			pos.first = MOUSE;
			pos.second = c;
			return pos;
		}
	}
	if (c == UP || c == DOWN || c == LEFT || c == RIGHT) {
		pos.first = ARROWS;
		pos.second = c;
	}
	else if (c == BACKSPACE) {
		pos.first = KEY;
		pos.second = c;
	}
	else if (c == ENTER) {
		pos.first = KEY;
		pos.second = c;
	}
	else if (c == ESC) {
		pos.first = KEY;
		pos.second = c;
	}
	else if (c == SPACE) {
		pos.first = KEY;
		pos.second = c;
	}
	else if (c != -1 && c != KEY_MOUSE) {
		pos.first = KEY;
		pos.second = c;
	}
	return pos;
}

void Model::increment_cur_x() {
	cur_x++;
}

void Model::increment_cur_y() {
	cur_y++;
}

void Model::decrement_cur_x() {
	cur_x--;
}

void Model::decrement_cur_y() {
	cur_y--;
}

int Model::get_lines_cnt() {
	return text.size();
}

MyString Model::get_line(int line_cnt) {
	return text[line_cnt];
}

int Model::get_line_length(int num) {
	return get_line(num).size();
}

void Model::reset_all() {
	mode = 0;
	path.clear();
	text.clear();
}

void Model::set_on_text_flag(bool flag) {
	on_text_flag = flag;
}

bool Model::get_on_text_flag() {
	return on_text_flag;
}

void Model::insert_char_in_cur_pos(char chr, int xPos, int yPos) {
	text[yPos].insert(xPos, 1, chr);
}

void Model::add_line_in_text(int xPos, int yPos) {
	MyString new_line = text[yPos];

	text[yPos].erase(xPos, text[yPos].size());
	text[yPos].append(2, ' ');

	new_line.erase(0, xPos);

	if (yPos == get_lines_cnt() - 1)
		text.insert(text.end(), new_line);
	else {
		text.insert(text.begin() + yPos + 1, new_line);
	}
}

void Model::delete_char_from_cur_pos(int xPos, int yPos) {
	text[yPos].erase(xPos - 1, 1);
	save_cur_x();
	save_cur_y();
}

void Model::add_prev_line_to_cur_line(int cur_line_num) {
	text[cur_line_num].erase(text[cur_line_num].size() - 2, 2);
	text[cur_line_num].append(text[cur_line_num + 1].c_str());
	text.erase(text.begin() + cur_line_num + 1);
}

void Model::set_mode(int mode) {
	this->mode = mode;
}

int Model::get_mode() {
	return mode;
}

vector<MyString> Model::words_in_string(MyString str) {
	string word;
	string text(str.c_str());
	stringstream ss(text);
	vector <MyString> array;
	while (ss >> word)
		array.push_back(word);
	return array;
}

pair<int, int> Model::find_substr_in_text(MyString str) {
	int line_cnt = get_lines_cnt();
	int cur_line = 0;
	pair<int, int> pos;
	while (cur_line != line_cnt) {
		int x = text[cur_line].find(str.c_str());
		if (x != -1) {
			pos.first = x;
			pos.second = cur_line;
			return pos;
		}
		cur_line++;
	}
	pos.first = -1;
	pos.second = -1;
	return pos;
}

void Model::delete_word_on_pos(int xPos, int yPos) {
	while (text[yPos][xPos] != ' ' && xPos != 0) {
		xPos--;
	}
	if (xPos != 0)
		xPos++;
	while (text[yPos][xPos] != ' ') {
		text[yPos].erase(xPos, 1);
	}
	text[yPos].erase(xPos, 1);
	text[yPos].append(2, ' ');
}

void Model::save_word_in_buffer_from_pos(int xPos, int yPos) {
	buffer.clear();
	while (text[yPos][xPos] != ' ' && xPos != 0) {
		xPos--;
	}
	if (xPos != 0)
		xPos++;
	while (text[yPos][xPos] != ' ') {
		buffer.append(1, text[yPos][xPos]);
		xPos++;
	}
}

void Model::save_line_in_buffer_from_pos(int yPos) {
	buffer.clear();
	int i = 0;
	const int line_len = get_line_length(yPos);
	while (i != line_len) {
		buffer.append(1, text[yPos][i]);
		i++;
	}
}

MyString Model::get_buffer() {
	return buffer;
}

void Model::add_str_to_text_on_pos(MyString str, int xPos, int yPos) {
	text[yPos].insert(xPos, str.c_str());
}
