/**
 * @file const.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef HEADER_DICTIONARY_H_
#define HEADER_DICTIONARY_H_

/* external libraries */
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
    BLACK,
    GRAY,
    WHITE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BROWN
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 900;

const std::map<Color, RGB> colors = {
    {BLACK, {0.f, 0.f, 0.f}},
    {GRAY, {0.75f, 0.75f, 0.75f}},
    {WHITE, {1.f, 1.f, 1.f}},
    {RED, {1.f, 0.f, 0.f}},
    {GREEN, {0.f, 1.f, 0.f}},
    {BLUE, {0.f, 0.f, 1.f}},
    {YELLOW, {0.96f, 0.81f, 0.004f}},
    {BROWN, {0.46f, 0.3f, 0.21f}}
};

#endif  // HEADER_DICTIONARY_H_
