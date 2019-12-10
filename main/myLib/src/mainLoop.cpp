#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#include "mainLoop.hpp"

using namespace m_engine;
using namespace std::chrono;

bool basicStartLoop(double time, int id_iteration) {
	std::cout << "start of loop " << id_iteration << " on time " << time << std::endl;
	return true;
}

bool basicEndLoop(double time, int id_iteration) {
	std::cout << "end of loop " << id_iteration << " on time " << time << std::endl;
	return true;
}

MainLoop::MainLoop(World& world, int fps):
	wantedTime(1. / fps), 
	start_loop(basicStartLoop), 
	end_loop(basicEndLoop), 
	world(world),
	mustStop(false)
{
}

void MainLoop::execute() {
	//id de l'iteration
	static int i = 0;
	//temps d'attente (en ms) avant la prochaine iteration
	long remainingTime;
	//temps (en s) du calcul (frame actuelle - precedente)
	double diff = wantedTime;
	//temps de reference
	time_point<system_clock> current_time, previous_time,
		base_time = system_clock::now();
	previous_time = base_time;
	int windowOK = 0;
	mustStop = mustStop || world.collisionDetected;
	while (windowOK == 0 && !mustStop) {
		//debut de la frame, on recupere le temps de ref
		current_time = system_clock::now();
		double timeRef = duration<double>(current_time - base_time).count();

		//fonction utilisateur, arrete la boucle si renvoie false
		if (!start_loop(timeRef, i)) break;
		//on met à jour le monde
		diff = duration<double>(current_time - previous_time).count();
		world.update(diff);
		//on l'affiche
		windowOK = world.render2DWindow();
		//fonction utilisateur, arrete la boucle si renvoie false
		if(!end_loop(timeRef, i)) break;

		//on recupere le temps que le calcul nous a pris
		time_point<system_clock> tmp = system_clock::now();
		diff = duration<double>(tmp - current_time).count();

		//on en deduit le temps qu'il nous reste avant la fin de la frame
		remainingTime = 1000 * (wantedTime - diff);

		if (remainingTime > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime));
		}
		i++;
		previous_time = current_time;
	}
}