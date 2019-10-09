#ifndef PARTICLE_CONTACT_RESOLVER
#define PARTICLE_CONTACT_RESOLVER

#include "particleContact.hpp"

#include "particle.hpp"
#include <vector>

namespace m_engine {
/*
	This class will check for collision and solve them
*/
	class ParticleContactResolver {
	public:
		ParticleContactResolver();
		~ParticleContactResolver() {}

		//checks for collisions, then solve them
		//returns whether there might still be some collisions
		bool resolveCollisions(double time, std::vector<Particle>& particles);
	private:
		std::vector<ParticleContact> collisions;
		std::vector<double> separationSpeeds;

		//look for any collision, given an array of Particles, 
		//store them in the collisions array
		void checkForCollision(std::vector<Particle>& particles);
		

		//get the size of th penetration between 2 particles on the vector between the 2
		static double getPenetration(const Particle* pa, const Particle* pb);
		//test used to check if two particles are considered colliding, used in checkForCollision
		static bool isColliding(const Particle* pa, const Particle* pb);
	};
}

#endif