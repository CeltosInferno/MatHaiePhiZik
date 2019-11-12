#ifndef FORCE_REGISTER
#define FORCE_REGISTER

#include <vector>
#include "particleForceGenerator.hpp"
#include "rigidBodyForceGenerator.hpp"

namespace m_engine {

	

	class ForceRegister {
	public:
		struct ForceStoredParticle {
			Particle* p;
			ParticleForceGenerator* Fg;

			bool operator==(const ForceStoredParticle& f) const{
				return (p == f.p && Fg == f.Fg);
			}
		};

		struct ForceStoredRigidBody {
			RigidBody* r;
			RigidBodyForceGenerator* Frg;

			bool operator==(const ForceStoredRigidBody& f) const {
				return (r == f.r && Frg == f.Frg);
			}
		};

		typedef std::vector <ForceStoredParticle> ParticleRegister;
		typedef std::vector <ForceStoredRigidBody> RigidBodyRegister;

		void add(Particle* p, ParticleForceGenerator* Fg);
		void add(RigidBody* r, RigidBodyForceGenerator* Frg);
		void applyForces(double time);
		void remove(Particle* p, ParticleForceGenerator* Fg);
		void remove(RigidBody* r, RigidBodyForceGenerator* Frg);
		void clear();

	private:
		ParticleRegister m_Preg;
		RigidBodyRegister m_Rreg;
	};

	

}

#endif