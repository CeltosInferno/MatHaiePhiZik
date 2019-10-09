#include <string>
#include <functional>

#include "world.hpp"


/* 
   classe qui controle le temps et execute la boucle de jeu, on 
   lui associe un World, un nombre d'execution par secondes,
   une fonction de controle definie dans main (sinon par defaut)
   et une fonction executee a chaque fin de frame qui peut determiner 
   la terminaison
*/
namespace m_engine {
	class MainLoop {
	public:
		MainLoop(World& world, int fps);
		~MainLoop() {}

		//set the funtion in parameters to be executed when a key is
		//pressed
		inline void setControls(const std::function<void(std::string key)>& controls) {
			world.renderer.OnKeyEvent(controls);
		}

		inline void setStartFrameFun(const std::function<bool(double, int)>& f) {
			start_loop = f;
		}

		inline void setEndFrameFun(const std::function<bool(double, int)>& f) {
			end_loop = f;
		}

		inline void setZoom(double z) {
			world.renderer.setZoom(z);
		}

		//lance la boucle principale
		void execute();
	private:
		double wantedTime;
		std::function<bool(double, int)> start_loop, end_loop;
		World& world;
	};
}