#include "MassSpringSystemSimulator.h"

MassSpringSystemSimulator::MassSpringSystemSimulator() : m_fMass(10.0), m_fStiffness(40.0), m_fDamping(0.01), m_iIntegrator(0), m_bIsGravityApplied(false),
	m_GravityVector(Vec3(0.0, -9.81, 0.0)), m_fBoundary(5.0), m_externalForce(Vec3(0.0, 0.0, 0.0)), m_mouse(Point2D{0, 0}), m_trackmouse(Point2D{ 0, 0 }),
	m_oldtrackmouse(Point2D{ 0, 0 }) {}

const char* MassSpringSystemSimulator::getTestCasesStr() {
	return "Demo 1,Demo 2: Euler,Demo 3: Midpoint,Demo 4: Complex";
}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass* DUC) {
	this->DUC = DUC;
	TwType TW_TYPE_INTEGRATION_METHOD = TwDefineEnumFromString("Integration Method", "Euler,Midpoint");
	switch (m_iTestCase) {
	case 0:break;
	case 1:break;
	case 2:
		TwAddVarRW(DUC->g_pTweakBar, "Integration Method", TW_TYPE_INTEGRATION_METHOD, &m_iIntegrator, "");
	case 3:
		TwAddVarRW(DUC->g_pTweakBar, "Mass", TW_TYPE_FLOAT, &m_fMass, "step=0.1 min=0.1");
		TwAddVarRW(DUC->g_pTweakBar, "Stiffness", TW_TYPE_FLOAT, &m_fStiffness, "step=1 min=1");
		TwAddVarRW(DUC->g_pTweakBar, "Damping", TW_TYPE_FLOAT, &m_fDamping, "step=0.1 min=0.1 max=1");
		TwAddVarRW(DUC->g_pTweakBar, "Gravity", TW_TYPE_BOOLCPP, &m_bIsGravityApplied, "");
	default:break;
	}
}

void MassSpringSystemSimulator::reset() {
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext) {
	std::mt19937 eng;
	std::uniform_real_distribution<float> randCol(0.0f, 1.0f);
	switch (m_iTestCase) {
	case 0:break;
	default:
		for (const auto& point : m_vPoints) {
			DUC->setUpLighting(Vec3(), 0.4 * Vec3(1, 1, 1), 100, 0.6 * Vec3(randCol(eng), randCol(eng), randCol(eng)));
			DUC->drawSphere(point.position, Vec3(0.1, 0.1, 0.1));
		}
		DUC->beginLine();
		for (const auto& spring : m_vSprings) {
			DUC->drawLine(m_vPoints.at(spring.firstPoint).position, Vec3(1, 1, 1), m_vPoints.at(spring.secondPoint).position, Vec3(1, 1, 1));
		}
		DUC->endLine();
		break;
	}
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase) {
	m_iTestCase = testCase;
	switch (m_iTestCase) {
	case 0:
		cout << "Demo 1" << endl;
		initDemo(0);
		calculateEulerTimestep(0.1);
		cout << "Euler results:" << endl;
		for (const auto& point : m_vPoints) {
			cout << point;
		}
		initDemo(0);
		calculateMidpointTimestep(0.1);
		cout << "Midpoint results:" << endl;
		for (const auto& point : m_vPoints) {
			cout << point;
		}
		break;
	case 1:
		cout << "Demo 2: Euler" << endl;
		initDemo(1);
		break;
	case 2:
		cout << "Demo 3: Midpoint" << endl;
		initDemo(2);
		break;
	case 3:
		cout << "Demo 4: Complex" << endl;
		initDemo(3);
		break;
	default:
		cout << "Empty Test" << endl;
		break;
	}
}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed) {
	Point2D mouseDiff;
	mouseDiff.x = m_trackmouse.x - m_oldtrackmouse.x;
	mouseDiff.y = m_trackmouse.y - m_oldtrackmouse.y;
	if (mouseDiff.x != 0 || mouseDiff.y != 0) {
		Mat4 worldViewInv = Mat4(DUC->g_camera.GetWorldMatrix() * DUC->g_camera.GetViewMatrix());
		worldViewInv = worldViewInv.inverse();
		Vec3 inputView = Vec3((float)mouseDiff.x, (float)-mouseDiff.y, 0);
		Vec3 inputWorld = worldViewInv.transformVectorNormal(inputView);
		// find a proper scale!
		float inputScale = 0.001f;
		inputWorld = inputWorld * inputScale;
	}
}

void MassSpringSystemSimulator::simulateTimestep(float timeStep) {

	switch (m_iTestCase) {
	case 1:
		calculateEulerTimestep(0.005);
		break;
	case 2:
		calculateMidpointTimestep(0.005);
		break;
	case 3:
		if (m_iIntegrator == 0) {
			calculateEulerTimestep(timeStep);
		}
		else {
			calculateMidpointTimestep(timeStep);
		}
		break;
	default:
		break;
	}
}

void MassSpringSystemSimulator::onClick(int x, int y) {
	// TODO: understand what it is and implement
}

void MassSpringSystemSimulator::onMouse(int x, int y) {
	// TODO: understand what it is and implement
}

void MassSpringSystemSimulator::setMass(float mass) {
	m_fMass = mass;
}

void MassSpringSystemSimulator::setStiffness(float stiffness) {
	m_fStiffness = stiffness;
}

void MassSpringSystemSimulator::setDampingFactor(float damping) {
	m_fDamping = damping;
}

int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 velocity, bool isFixed) {
	m_vPoints.push_back(Point(position, velocity, Vec3(0, 0, 0), isFixed));
	return m_vPoints.size() - 1;
}

void MassSpringSystemSimulator::addSpring(int firstPoint, int secondPoint, float initialLength) {
	m_vSprings.push_back(Spring(firstPoint, secondPoint, m_fStiffness, initialLength));
}

int MassSpringSystemSimulator::getNumberOfMassPoints() {
	return m_vPoints.size();
}

int MassSpringSystemSimulator::getNumberOfSprings() {
	return m_vSprings.size();
}

Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index) {
	return m_vPoints.at(index).position;
}

Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index) {
	return m_vPoints.at(index).velocity;
}

void MassSpringSystemSimulator::calculateEulerTimestep(float timestep) {
	resetForcesAndApplyGravity();

	calculateNewForces();

	calculateNewPositions(timestep);

	calculateNewVelocities(timestep);

	checkBoundaries();
}

void MassSpringSystemSimulator::calculateMidpointTimestep(float timestep) {
	std::vector<Point> tempPoints;
	tempPoints.assign(m_vPoints.begin(), m_vPoints.end());

	resetForcesAndApplyGravity();
	
	calculateNewForces();

	calculateNewPositions(timestep / 2);

	calculateNewVelocities(timestep / 2);

	resetForcesAndApplyGravity();

	calculateNewForces();

	std::vector<Vec3> forceVector;

	for (const auto& point : m_vPoints) {
		forceVector.push_back(point.force);
	}

	m_vPoints.assign(tempPoints.begin(), tempPoints.end());

	for (auto i = 0; i < m_vPoints.size(); i++) {
		m_vPoints.at(i).force = forceVector.at(i);
	}

	calculateNewPositions(timestep);

	calculateNewVelocities(timestep);

	checkBoundaries();
}

void MassSpringSystemSimulator::resetForcesAndApplyGravity() {
	for (auto& point : m_vPoints) {
		if (m_bIsGravityApplied) {
			point.force = m_GravityVector;
		}
		else {
			point.force = Vec3();
		}
	}
}

void MassSpringSystemSimulator::calculateNewForces() {
	for (const auto& spring : m_vSprings) {
		Vec3 vectorBetweenPoints = getPositionOfMassPoint(spring.firstPoint) - getPositionOfMassPoint(spring.secondPoint);
		Vec3 currentLength = norm(vectorBetweenPoints);
		Vec3 springForce = -m_fStiffness * (currentLength - spring.initialLength) *
			getNormalized(vectorBetweenPoints) / m_fMass;
		Vec3 firstPointDamping = -m_fDamping * getVelocityOfMassPoint(spring.firstPoint);
		Vec3 secondPointDamping = -m_fDamping * getVelocityOfMassPoint(spring.secondPoint);
		m_vPoints.at(spring.firstPoint).force += springForce;
		m_vPoints.at(spring.firstPoint).force += firstPointDamping;
		m_vPoints.at(spring.secondPoint).force -= springForce;
		m_vPoints.at(spring.secondPoint).force += secondPointDamping;
	}
}

void MassSpringSystemSimulator::calculateNewPositions(float timestep) {
	for (auto& point : m_vPoints) {
		if (!point.isFixed) {
			point.position += point.velocity * timestep;
		}
	}
}

void MassSpringSystemSimulator::calculateNewVelocities(float timestep) {
	for (auto& point : m_vPoints) {
		point.velocity += point.force * (timestep / m_fMass);
	}
}

void MassSpringSystemSimulator::checkBoundaries() {
	for (auto& point : m_vPoints) {
		if (point.position.x > m_fBoundary) {
			point.position.x = m_fBoundary;
			point.velocity.x *= -1;
		}
		else if (point.position.x < -m_fBoundary) {
			point.position.x = -m_fBoundary;
			point.velocity.x *= -1;
		}
		if (point.position.y > m_fBoundary) {
			point.position.y = m_fBoundary;
			point.velocity.y *= -1;
		}
		else if (point.position.y < 0) {
			point.position.y = 0;
			point.velocity.y *= -1;
		}
		if (point.position.z > m_fBoundary) {
			point.position.z = m_fBoundary;
			point.velocity.z *= -1;
		}
		else if (point.position.z < -m_fBoundary) {
			point.position.z = -m_fBoundary;
			point.velocity.z *= -1;
		}
	}
}

void MassSpringSystemSimulator::initDemo(int demoNumber) {
	m_vPoints.clear();
	m_vSprings.clear();

	// Initialize the first three demos since they all share the same data
	if (demoNumber >= 0 && demoNumber <= 2) {
		int firstPoint = addMassPoint(Vec3(), Vec3(-1, 0, 0), false);
		int secondPoint = addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
		addSpring(firstPoint, secondPoint, 1.0);
		setMass(10.0);
		setStiffness(40.0);
		setDampingFactor(0);
	}
	// Initialize the last demo
	else if (demoNumber == 3) {
		int firstPoint = addMassPoint(Vec3(), Vec3(), false);
		int secondPoint = addMassPoint(Vec3(0, 0, 1), Vec3(), false);
		int thirdPoint = addMassPoint(Vec3(0, 1, 0), Vec3(), false);
		int fourthPoint = addMassPoint(Vec3(0, 1, 1), Vec3(), false);
		int fifthPoint = addMassPoint(Vec3(1, 0, 0), Vec3(), false);
		int sixthPoint = addMassPoint(Vec3(1, 0, 1), Vec3(), false);
		int seventhPoint = addMassPoint(Vec3(1, 1, 0), Vec3(), false);
		int eighthPoint = addMassPoint(Vec3(1, 1, 1), Vec3(), false);
		int ninthPoint = addMassPoint(Vec3(0, 0, 2), Vec3(), false);
		int tenthPoint = addMassPoint(Vec3(0, 2, 0), Vec3(), false);

		addSpring(firstPoint, thirdPoint, 1.0);
		addSpring(thirdPoint, fifthPoint, 1.0);
		addSpring(fifthPoint, seventhPoint, 1.0);
		addSpring(seventhPoint, ninthPoint, 1.0);
		addSpring(secondPoint, fourthPoint, 1.0);
		addSpring(fourthPoint, sixthPoint, 1.0);
		addSpring(sixthPoint, eighthPoint, 1.0);
		addSpring(eighthPoint, tenthPoint, 1.0);
	}
}


void MassSpringSystemSimulator::applyExternalForce(Vec3 force) {
	m_externalForce = force;
}
