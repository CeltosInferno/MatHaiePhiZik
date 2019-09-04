#include "particle.hpp"

using namespace m_engine;

Particle::Particle() : m_inversMass(0), m_pos(), m_vel(), m_acc(){

}

Particle::Particle(double mass, double posX, double posY, double posZ, double velX, double velY, double velZ, double accX, double accY, double accZ) {
	setMass(mass);
	setPos(posX, posY, posZ);
	setVel(velX, velY, velZ);
	setAcc(accX, accY, accZ);
}


Particle::~Particle() {
}


// GETTERS

double Particle::getInversMass() const {
	return m_inversMass;
}

// SETTERS

void Particle::setMass(double mass) {
	if (mass == 0) {
		std::cerr << "error : null mass";
	}
	else {
		m_inversMass = 1 / mass;
	}
}

void Particle::setPos(Vector3D pos) {
	m_pos = pos;
}

void Particle::setVel(Vector3D vel) {
	m_vel = vel;
}

void Particle::setAcc(Vector3D acc) {
	m_acc = acc;
}

void Particle::setPos(double x, double y, double z) {
	m_pos = Vector3D(x, y, z);
}

void Particle::setVel(double x, double y, double z) {
	m_vel = Vector3D(x, y, z);
}

void Particle::setAcc(double x, double y, double z) {
	m_acc = Vector3D(x, y, z);
}