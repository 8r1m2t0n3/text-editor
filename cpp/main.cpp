#include "MVC.h"

int main() {
	View view;
	Model model;
	Controller controller(model, view);
	controller.run();
}
