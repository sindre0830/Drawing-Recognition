#ifndef PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_COLORS_H_
#define PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_COLORS_H_

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

#endif  // PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_COLORS_H_
