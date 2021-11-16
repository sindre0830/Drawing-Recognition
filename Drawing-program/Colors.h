/**
 * @file Colors.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-09
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

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
    blue,
    yellow
};

extern std::map<Color, RGB> colors;

void initColors();
RGB findColor(Color color);

#endif  // COLORS_H_
