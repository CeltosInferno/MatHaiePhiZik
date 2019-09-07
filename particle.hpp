#ifndef PARTICLE
#define PARTICLE

#include <string>
#include <iostream>
#include "vector3d.hpp"

namespace m_engine {

	class Particle {
	public:

		Particle();
		Particle(double mass, double damping = 1, double posX = 0, double posY = 0, double posZ = 0, double velX = 0, double velY = 0, double velZ = 0, double accX = 0, double accY = 0, double accZ = 0);
		~Particle();

		// GETTERS
		double getInversMass() const;

		// SETTERS
		void setMass(double mass);
		void setDamping(double damping);
		void setPos(Vector3D pos);
		void setVel(Vector3D vel);
		void setAcc(Vector3D acc);
		void setPos(double x, double y, double z);
		void setVel(double x, double y, double z);
		void setAcc(double x, double y, double z);


		// INTEGRATEUR
		void integrate(long time);

		void render();

	private:
		double m_inversMass;
		double m_damping;
		Vector3D m_pos, m_vel, m_acc;
	};
}

#endif /* PARTICLE */
