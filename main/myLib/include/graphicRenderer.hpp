#ifndef GRAPHICRENDERER
#define GRAPHICRENDERER

#include <iostream>
#include <string>
#include <vector>
#include <functional>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "particle.hpp"


namespace m_engine {

	class GraphicRenderer {
	public:
		GraphicRenderer(unsigned int WIDTH = 800, unsigned int HEIGHT = 600, std::string WindowName = "Graphic View");
		//turn a vector of particle into vertices to render as triangles
		//return 0 if everithing is OK, 1 if the window should or have close
		int renderCircles(const std::vector<Particle>&);
		//Add a callback function reaction to arrow key event
		void OnKeyEvent(std::function<void(std::string dir)> f);

		inline void setZoom(double _zoom) { zoom = _zoom; }
	private:
		GLFWwindow* window;
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;
		void particleToCircle(const std::vector<Particle>&);
		void processInput(GLFWwindow* window);
		std::vector<float> fvertices;
		int shaderProgram;
		std::vector<std::function<void(std::string dir)>> callBackOnArrowKey;
		double zoom;
	};

}

#endif