#include "RigidBody.h"

RigidBody::RigidBody(Vec3 position, Quat orientation, Vec3 angularMomentum,
	Vec3 angularVelocity, Vec3 linearVelocity, int mass, Vec3 size) : position(position), orientation(orientation), angularMomentum(angularMomentum),
	angularVelocity(angularVelocity), linearVelocity(linearVelocity), mass(mass) {
	//TODO: Calculate corner points.
	cornerPoints.push_back(Vec3(position.x - size.x / 2, position.y - size.y / 2, position.z - size.z / 2));
	cornerPoints.push_back(Vec3(position.x + size.x / 2, position.y - size.y / 2, position.z - size.z / 2));
	cornerPoints.push_back(Vec3(position.x - size.x / 2, position.y + size.y / 2, position.z - size.z / 2));
	cornerPoints.push_back(Vec3(position.x - size.x / 2, position.y - size.y / 2, position.z + size.z / 2));
	cornerPoints.push_back(Vec3(position.x + size.x / 2, position.y + size.y / 2, position.z - size.z / 2));
	cornerPoints.push_back(Vec3(position.x + size.x / 2, position.y - size.y / 2, position.z + size.z / 2));
	cornerPoints.push_back(Vec3(position.x - size.x / 2, position.y + size.y / 2, position.z + size.z / 2));
	cornerPoints.push_back(Vec3(position.x + size.x / 2, position.y + size.y / 2, position.z + size.z / 2));
}

RigidBody::RigidBody(Vec3 position, int mass, Vec3 size) : position(position), mass(mass) {
	cornerPoints.push_back(Vec3(position.x - size.x / 2, position.y - size.y / 2, position.z - size.z / 2));
	cornerPoints.push_back(Vec3(position.x + size.x / 2, position.y - size.y / 2, position.z - size.z / 2));
	cornerPoints.push_back(Vec3(position.x - size.x / 2, position.y + size.y / 2, position.z - size.z / 2));
	cornerPoints.push_back(Vec3(position.x - size.x / 2, position.y - size.y / 2, position.z + size.z / 2));
	cornerPoints.push_back(Vec3(position.x + size.x / 2, position.y + size.y / 2, position.z - size.z / 2));
	cornerPoints.push_back(Vec3(position.x + size.x / 2, position.y - size.y / 2, position.z + size.z / 2));
	cornerPoints.push_back(Vec3(position.x - size.x / 2, position.y + size.y / 2, position.z + size.z / 2));
	cornerPoints.push_back(Vec3(position.x + size.x / 2, position.y + size.y / 2, position.z + size.z / 2));
}