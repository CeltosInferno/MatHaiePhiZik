#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include "world.hpp"
#include "particle.hpp"

using namespace m_engine;

int main() {
  
	World myWorld;
	myWorld.start();
	long wantedTime = 1000 / 10;
	long time, remainingTime, duration = wantedTime;

	while (1) {

		time = clock();

		//update et render avec la variable duration
		myWorld.update(duration);
		myWorld.render();

		duration = clock() - time;
		remainingTime = wantedTime - duration;

		if (remainingTime > 0) {
			duration = wantedTime;
			std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime));
		}

	}
	return 0;
}
