#ifndef WORLD
#define WORLD

#include <vector>
#include "particle.hpp"

namespace m_engine {

  class World {
  public:
    World();
    ~World();

    void start();
    void update(double time);
    void render();
		
    void addParticle(const Particle& part);

  private :
    std::vector<Particle> particles;
  };
}

#endif /* WORLD */
