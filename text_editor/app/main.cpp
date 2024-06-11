#include "text_editor/include/mvc.h"

int main() {
	View view;
	Model model;
	Controller controller(model, view);
	controller.run();
}
