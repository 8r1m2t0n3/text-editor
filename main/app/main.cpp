#include "view.h"
#include "model.h"
#include "controller.h"

int main() {
	View view;
	Model model;
	Controller controller(model, view);
	controller.run();
}
