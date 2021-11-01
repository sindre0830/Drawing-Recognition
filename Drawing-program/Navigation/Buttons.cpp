#include "Buttons.h"

/**
 *	Constructor. 
 */
Buttons::Buttons() {

}

/**
 *	Deconstructor.
 */
Buttons::~Buttons() {
	while (!buttons.empty()) {
		auto it = buttons.begin();
		delete* it;
		buttons.erase(it);
	}
}

/**
 *	Add a new button.
 */
void Buttons::addButton(Rect rect) {
	Button* button = new Button(rect);
	buttons.push_back(button);
}

/**
 *	Draw all buttons on screen.
 */
void Buttons::draw() {
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
		(*it)->draw();
}

/**
 *	Check if a button is clicked.
 */
void Buttons::detectClick(double x, double y) {
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
		(*it)->detectClick(x, y);
}