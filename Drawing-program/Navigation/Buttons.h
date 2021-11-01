#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "Button.h"

#include <vector>

/**
 *	Class for controlling all buttons.
 */
class Buttons {
private:
	std::vector<Button*> buttons;
public:
	Buttons();
	~Buttons();

	void addButton(Rect rect);
	void draw();
	void detectClick(double x, double y);
};

#endif // !__BUTTONS_H

