#ifndef PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_PAINTBRUSH_POINT_H_
#define PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_PAINTBRUSH_POINT_H_

/**
 *	Class for creating a point.
 */
class Point {
 private:
    float x, y,
          size,
          r, g, b;

 public:
    Point() { }
    Point(float x, float y, float size, float r = 1.f, float g = 0.f, float b = 0.f);
    ~Point() {}

    float getX() { return x; }
    float getY() { return y; }
    float getSize() { return size; }

    float getR() { return r; }
    float getG() { return g; }
    float getB() { return b; }
};

#endif  // PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_PAINTBRUSH_POINT_H_
