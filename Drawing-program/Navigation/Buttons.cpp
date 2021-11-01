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