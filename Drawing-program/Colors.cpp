#include "Colors.h"

/**
 *	Constructor.
 */
Colors::Colors() {
	// Create the available colors
	RGB blackVal = { 0.f, 0.f, 0.f };
	RGB redVal = { 1.f, 0.f, 0.f };
	RGB greenVal = { 0.f, 1.f, 0.f };
	RGB blueVal = { 0.f, 0.f, 1.f };

	// Insert them to map with their names as the key
	colors.insert({ black, blackVal });
	colors.insert({ red, redVal });
	colors.insert({ green, greenVal });
	colors.insert({ blue, blueVal });
}

/**
 *	Find the color in the color map.
 * 
 *	@param color - The name of the color to be found
 *	@return The RGB values of the color
 */
RGB Colors::findColor(Color color) {
	return colors.find(color)->second;
}