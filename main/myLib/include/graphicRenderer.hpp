#ifndef GRAPHICRENDERER
#define GRAPHICRENDERER

#include <iostream>
#include <string>
#include <vector>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "particle.hpp"


namespace m_engine {

	class GraphicRenderer {
	public:
		GraphicRenderer(unsigned int WIDTH = 800, unsigned int HEIGHT = 600, std::string WindowName = "Graphic View");
		//~GraphicRenderer();
		int renderCircles(const std::vector<Particle>&);
	private:
		GLFWwindow* window;
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;
		void particleToCircle(const std::vector<Particle>&);
		std::vector<float> fvertices;
		int shaderProgram;
	};

}

#endif