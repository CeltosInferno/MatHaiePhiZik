#ifndef GRAPHICRENDERER
#define GRAPHICRENDERER

#include <iostream>
#include <string>
#include <vector>
#include <functional>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>


#include "particle.hpp"
#include "matrix4.hpp"

#include "rigidBody.hpp"


namespace m_engine {

	class GraphicRenderer {
	public:
		GraphicRenderer(unsigned int WIDTH = 800, unsigned int HEIGHT = 600, std::string WindowName = "Graphic View");
		//turn a vector of rigidBody into vertices to render as triangles
		//return 0 if everithing is OK, 1 if the window should or have close
		int renderCubes(const std::vector<RigidBody>&,
						const std::vector<Particle>&);
		//Add a callback function reaction to arrow key event
		void OnKeyEvent(std::function<void(std::string dir)> f);

		inline void setZoom(double _zoom) { zoom = _zoom; }
	private:
		GLFWwindow* window;
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;
		//turn a vector of particle into vertices to render as triangles
		void particleToCube(const Particle& p);
		void renderCubes(const RigidBody& body);
		void addVectorToVertices(const Vector3D& v);
		void processInput(GLFWwindow* window);
		std::vector<float> fvertices;
		int shaderProgram;
		std::vector<std::function<void(std::string dir)>> callBackOnArrowKey;
		double zoom;
	};

}

#endif