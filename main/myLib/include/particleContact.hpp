#ifndef PARTICLE_CONTACT
#define PARTICLE_CONTACT

#include "particle.hpp"


namespace m_engine {

	// cette classe décrit un contact entre 2 particules, et le résout. 
	//Si contact avec le sol, la 2è particule est Floor
	class ParticleContact {
	public:
		//on defini le sol comme suit
		static Particle Floor;
		static Vector3D NormalFloor;

		ParticleContact(Particle* p1, Particle* p2, double c, double penetration);
		~ParticleContact() {};

		//résout la collision
		void resolve(double time);

		//résout les impulsions
		void resolveVelocity(double time);

		//résout l'interpénétration
		void resolvePenetration(double time);

		//calcul la vitesse d'éloignement
		double calculVs() const;


	private:

		Particle* particles[2];

		//coefficient de restitution de l'énergie
		double restitutionCoeff;

		//vecteur normal du contact
		Vector3D n;

		//taille de l'interpénétration
		double penetration;

	};

}

#endif