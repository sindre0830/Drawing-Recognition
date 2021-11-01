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
};

#endif // !__BUTTONS_H

