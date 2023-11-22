#include "Point.h"

Point::Point(Vec3 position, Vec3 velocity, Vec3 force,bool isFixed = false) :
	position(position), velocity(velocity), force(force),isFixed(isFixed) {}

std::ostream& operator<<(std::ostream& output, const Point& point)
{
	output << "position is: " << point.position << std::endl << "velocity is: " << point.velocity << std::endl << "force is: " << point.force << std::endl;
	return output;
}
