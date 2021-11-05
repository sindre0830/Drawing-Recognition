#ifndef __COLORS_H
#define __COLORS_H

#include <map>

/**
 *	RGB values.
 */
struct RGB {
	float r, g, b;
};

/**
 *	Color names.
 */
enum Color {
	black,
	red,
	green,
	blue
};

extern std::map<Color, RGB> colors;

void initColors();
RGB findColor(Color color);

#endif