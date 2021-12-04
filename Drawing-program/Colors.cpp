/**
 * @file Colors.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-09
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "Colors.h"

std::map<Color, RGB> colors;

/**
 *	Initialize all color values.
 */
void initColors() {
    // Create the available colors
    RGB blackVal = { 0.f, 0.f, 0.f };
    RGB redVal = { 1.f, 0.f, 0.f };
    RGB greenVal = { 0.f, 1.f, 0.f };
    RGB blueVal = { 0.f, 0.f, 1.f };
    RGB yellowVal = { 0.96f, 0.81f, 0.004 };

    // Insert them to map with their names as the key
    colors.insert({ black, blackVal });
    colors.insert({ red, redVal });
    colors.insert({ green, greenVal });
    colors.insert({ blue, blueVal });
    colors.insert({ yellow, yellowVal });
}

/**
 *	Find the color in the color map.
 * 
 *	@param color - The name of the color to be found
 *	@return The RGB values of the color
 */
RGB findColor(Color color) {
    return colors.find(color)->second;
}
