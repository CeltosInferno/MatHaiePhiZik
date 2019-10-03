#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include "world.hpp"
#include "particle.hpp"

using namespace m_engine;
using namespace std::chrono;

#define FPS 10

int main() {
  
	World myWorld;


	myWorld.start();

	char entry = 'a';
	while (entry != '1' && entry != '2' && entry != '3' && entry != '4')
	{
		std::cout << "choisissez un projetil" << std::endl << "1 : sans damping" << std::endl << "2 : 0.99 de damping" << std::endl << "3 : 0.9 de damping" << std::endl << "4 : 0.5 de damping sans gravité" << std::endl << "choix :";
		std:: cin >> entry;
	}

	switch (entry) {
	case '1' :
		myWorld.addParticle(Particle(2, 1, Vector3D(0, 0, 0), Vector3D(0, 15, 0), Vector3D(0, -9.8, 0)));
		break;
	case '2' :
		myWorld.addParticle(Particle(1, 0.99, Vector3D(0, 1, 0), Vector3D(0, 10, 0), Vector3D(0, -9.8, 0)));
		break;
	case '3':
		myWorld.addParticle(Particle(3, 0.9, Vector3D(0, 2, 0), Vector3D(0, 15, 0), Vector3D(0, -9.8, 0)));
		break;
	case '4':
		myWorld.addParticle(Particle(3, 0.5, Vector3D(0, 2, 0), Vector3D(0, 10, 0), Vector3D(0, 0, 0)));
		break;
	}



	//durée (en s) du temps necessaire entre chaque iteration
	double wantedTime = 1. / FPS;

	//temps d'attente (en ms) avant la prochaine iteration
	long remainingTime;

	//temps (en s) du calcul (frame actuelle - precedente)
	double diff = wantedTime;

	//temps de reference
	time_point<system_clock> current_time, previous_time,
							 base_time = system_clock::now();

	previous_time = base_time;
	while (1) {
		//debut de la frame, on recupere le temps de ref
		current_time = system_clock::now();

		std::cout << "temps : " << duration<double>(current_time - base_time).count() << std::endl;
		diff = duration<double>(current_time - previous_time).count();

		//on met à jour le monde
		myWorld.update( diff );
		//on l'affiche
		myWorld.render2DWindow();

		//on recupere le temps que le calcul nous a pris
		time_point<system_clock> tmp = system_clock::now();
		diff = duration<double>(tmp - current_time).count();
		
		//on en deduit le temps qu'il nous reste avant la fin de la frame
		remainingTime = 1000*(wantedTime - diff);

		if (remainingTime > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime));
		}
		previous_time = current_time;
	}
	return 0;
}
