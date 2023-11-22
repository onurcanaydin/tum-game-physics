#include "Spring.h"

Spring::Spring(int firstPoint, int secondPoint, float stiffness, float initialLength) :
	firstPoint(firstPoint), secondPoint(secondPoint), stiffness(stiffness), initialLength(initialLength) {}
