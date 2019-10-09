#ifndef PARTICLE_CONTACT_GENERATOR
#define PARTICLE_CONTACT_GENERATOR

/*
Interface de generation de contact, unused
a utiliser dans particleContactResolver (situe dans World)
*/
namespace m_engine {
	class ParticleContactGenerator {
	public:
		virtual ~ParticleContactGenerator() {}
		virtual void addContact()=0;
	};
}

#endif