/**
 * @file Point.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-11-09
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "Point.h"

/**
 *	Constructor.
 *
 *	@param x - The x coordinate of the point
 *	@param y - The y coordinate of the point
 *	@param size - The size of the point
 *	@param r - Red 
 *	@param g - Green
 *	@param b - Blue
 */
Point::Point(float x, float y, float size, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->size = size;

    this->r = r;
    this->g = g;
    this->b = b;
}
