#ifndef __POINT_H
#define __POINT_H

/**
 *	Class for creating a point.
 */
class Point {
private:
	float x, y,
		  size;
public:
	Point() { }
	Point(float x, float y, float size);
	~Point();

	float getX() { return x; }
	float getY() { return y; }
	float getSize() { return size; }
};

#endif // !__POINT_H

