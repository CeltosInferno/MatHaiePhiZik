#include "particle.hpp"
#include <cmath>
#include <iostream>

using namespace m_engine;

Particle::Particle() : m_inversMass(0), m_damping(1), m_pos(), m_vel(), m_acc(){

}

//Constructor using only doubles
Particle::Particle(double mass, double damping,
		   double posX, double posY, double posZ,
		   double velX, double velY, double velZ,
		   double accX, double accY, double accZ)
  : m_inversMass(1/mass), m_damping(damping),
    m_pos(posX, posY, posZ),
    m_vel(velX, velY, velZ),
    m_acc(accX, accY, accZ)
{}

//Constructor using Vector3D to describe the position, velocity and acceleration of the particule
Particle::Particle(double mass, double damping, const Vector3D& pos,
	 const Vector3D& vel, const Vector3D& acc):
  m_inversMass(1/mass), m_damping(damping),
  m_pos(pos), m_vel(vel), m_acc(acc)
{}


Particle::~Particle() {}


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

void Particle::setDamping(double damping) {
	if (damping <= 1 && damping >= 0) {
		m_damping = damping;
	}
}

// INTEGRATOR
// make the particule move according to its position, velocity and acceleration
void Particle::integrate(double time) {
	
  //update of pos
  this->m_pos += m_vel * time;

  //update of vel
  m_vel = m_vel * pow(m_damping, time) + m_acc * time;

}
