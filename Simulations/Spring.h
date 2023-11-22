#ifndef SPRING_h
#define SPRING_h

#include "util/vectorbase.h"
#include "Point.h"
using namespace GamePhysics;

class Spring
{
public:
	int firstPoint, secondPoint;
	float stiffness, initialLength;

	Spring(int firstPoint, int secondPoint, float stiffness, float initialLength);
};

#endif
