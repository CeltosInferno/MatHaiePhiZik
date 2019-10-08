#ifndef PARTICLE_CONTACT
#define PARTICLE_CONTACT

#include "particle.hpp"


namespace m_engine {

	// cette classe d�crit un contact entre 2 particules, et le r�sout. Si contact avec le sol, la 2� particule est NULL
	class ParticleContact {
	public:
		ParticleContact(Particle* p1, Particle* p2, double c, double penetration);
		~ParticleContact() {};

		//r�sout la collision
		void resolve(double time);

		//r�sout les impulsions
		void resolveVelocity(double time);

		//r�sout l'interp�n�tration
		void resolvePenetration(double time);

		//calcul la vitesse d'�loignement
		double calculVs() const;


	private:

		Particle* particles[2];

		//coefficient de restitution de l'�nergie
		double restitutionCoeff;

		//vecteur normal du contact
		Vector3D n;

		//taille de l'interp�n�tration
		double penetration;

	};

}

#endif