#ifndef PARTICLE
#define PARTICLE

#include <string>
#include <iostream>
#include "vector3d.hpp"

namespace m_engine {

	class Particle {
	public:

		// GETTERS

		// SETTERS



		// INTEGRATEUR
		void integrate(float time);

	private:
		double m_inversMass;
		Vector3D m_pos, m_vel, m_acc;
	};
}

#endif /* PARTICLE */
