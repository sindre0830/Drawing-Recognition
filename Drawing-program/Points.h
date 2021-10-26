#ifndef __POINTS_H
#define __POINTS_H

#include "Point.h"

#include <glad/glad.h>

#include <vector>

/**
 *	Class for controlling points.
 */
class Points {
private:
	std::vector<Point*> points;
public:
	Points();
	~Points();

	std::vector<Point*> getPoints() { return points; }
	int getPointsSize() { return points.size(); }

	void createPoint(double x, double y, float g);
	void draw();
	void init();
};

#endif // !__POINTS_H
