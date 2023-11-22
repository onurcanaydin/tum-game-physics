#ifndef POINT_h
#define POINT_h

#include "util/vectorbase.h"
#include <ostream>
using namespace GamePhysics;

class Point {
public:
	Vec3 position, velocity, force;
	bool isFixed;

	Point(Vec3 position, Vec3 velocity, Vec3 force, bool isFixed);

	friend std::ostream& operator<<(std::ostream& output, const Point& point);
};

std::ostream& operator<<(std::ostream& output, const Point& point);

#endif
