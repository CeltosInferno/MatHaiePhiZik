#ifndef WORLD
#define WORLD

#include <vector>
#include "particle.hpp"
#include "graphicRenderer.hpp"

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

	//2D rendering in OPenGL Window
	int render2DWindow();

  private :
    std::vector<Particle> particles;
	GraphicRenderer renderer;
  };
}

#endif /* WORLD */
