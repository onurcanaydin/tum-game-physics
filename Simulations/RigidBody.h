#ifndef RIGIDBODY_h
#define RIGIDBODY_h

#include "Simulator.h"

using namespace GamePhysics;

class RigidBody
{
public:
	RigidBody(Vec3 position, Quat orientation, Vec3 angularMomentum,
		Vec3 angularVelocity, Vec3 linearVelocity, int mass, Vec3 size);

	RigidBody(Vec3 position, int mass, Vec3 size);

	Vec3 position;
	Quat orientation;
	Vec3 angularMomentum;
	Vec3 angularVelocity;
	Vec3 linearVelocity;
	int mass;
	Vec3 force;
	Vec3 torque;
	Mat4 inertiaTensor;
	Mat4 inverseInertiaTensor;
	Vec3 worldSpace;
	vector<Vec3> cornerPoints;
};
#endif
