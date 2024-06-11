#include "text-editor/include/view.h"
#include "text-editor/include/model.h"
#include "text-editor/include/controller.h"

int main() {
	View view;
	Model model;
	Controller controller(model, view);
	controller.run();
}
