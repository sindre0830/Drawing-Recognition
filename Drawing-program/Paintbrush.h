#ifndef __PAINTBRUSH_H
#define __PAINTBRUSH_H

#include <glad/glad.h>

#include "Point.h"

#include <vector>

/**
 *	Class for controlling points.
 */
class Paintbrush {
private:
	std::vector<Point*> points;
public:
	Paintbrush();
	~Paintbrush();

	std::vector<Point*> getPoints() { return points; }
	int getPointsSize() { return points.size(); }

	void draw();
	void init();
};

#endif // !__POINTS_H
