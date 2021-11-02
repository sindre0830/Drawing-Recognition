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

/**
 *	Class for storing colors.
 */
class Colors {
private:
	std::map<Color, RGB> colors;
public:
	Colors();
	~Colors() {}

	RGB findColor(Color color);
};

#endif