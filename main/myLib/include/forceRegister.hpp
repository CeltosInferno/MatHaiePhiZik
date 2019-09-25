#ifndef FORCE_REGISTER
#define FORCE_REGISTER

#include <vector>
#include "particleForceGenerator.hpp"

namespace m_engine {

	

	class ForceRegister {
	public:
		struct ForceStored {
			Particle* p;
			ParticleForceGenerator* Fg;

			bool operator==(const ForceStored& f) const{
				return (p == f.p && Fg == f.Fg);
			}
		};

		typedef std::vector <ForceStored> Register;

		void add(Particle* p, ParticleForceGenerator* Fg);
		void remove(Particle* p, ParticleForceGenerator* Fg);
		void clear();

	private:
		Register m_reg;
	};

	

}

#endif