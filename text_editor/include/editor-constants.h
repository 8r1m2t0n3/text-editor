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