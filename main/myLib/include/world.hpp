#ifndef WORLD
#define WORLD

#include <vector>
#include "particle.hpp"
#include "forceRegister.hpp"
#include "graphicRenderer.hpp"

namespace m_engine {

  class World {
  public:
    World();
    ~World();

	//MainLoop can access non-public attributes such as renderer
	friend class MainLoop;

    void start();

    //Add a particle in the world
    void addParticle(const Particle& part);

    //Update all the particles of the world
    void update(double time);

    //2D rendering in a terminal
    void renderBash();

	//2D rendering in OPenGL Window
	int render2DWindow();

	//Pour des raisons d'accès lors du travail des forces, 
	//le tableau est publique
	//dans le futur, soit faire tableau de ref/pointeurs,
	//soit mettre des accesseurs
	std::vector<Particle> particles;
	ForceRegister forceRegister;

  private :
	GraphicRenderer renderer;
  };
}

#endif /* WORLD */
