#ifndef COLORS_H_
#define COLORS_H_

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

#endif  // COLORS_H_
