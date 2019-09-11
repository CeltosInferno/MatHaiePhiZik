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

    //Add a particle in the world
    void addParticle(const Particle& part);

    //Update all the particles of the world
    void update(double time);

    //2D rendering in a terminal
    void renderBash();

  private :
    std::vector<Particle> particles;
  };
}

#endif /* WORLD */
