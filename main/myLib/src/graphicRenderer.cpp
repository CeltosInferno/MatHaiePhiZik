#include "graphicRenderer.hpp"

#include <iostream>
#include <string>
#include <algorithm>

#include "vector3D.hpp"
#include "particle.hpp"


using namespace m_engine;

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//This function process the input when they are captured
void GraphicRenderer::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		zoom-=1;
		if (zoom <= 0) {
			zoom = 1;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		zoom+=1;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		for (std::function<void(std::string dir)> f : callBackOnArrowKey)
		{
			f("LEFT");
		};
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		for (std::function<void(std::string dir)> f : callBackOnArrowKey)
		{
			f("RIGHT");
		};
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		for (std::function<void(std::string dir)> f : callBackOnArrowKey)
		{
			f("UP");
		};
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		for (std::function<void(std::string dir)> f : callBackOnArrowKey)
		{
			f("DOWN");
		};
	}
}


//Shader sources
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

GraphicRenderer::GraphicRenderer(unsigned int WIDTH, unsigned int HEIGHT, std::string WindowName) {

	//Attributes assignement
	SCR_WIDTH = WIDTH;
	SCR_HEIGHT = HEIGHT;
	//Library initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WindowName.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	zoom = 1;

	//Enable depth tests so that 3D polygons will have the correct depth rendering
	glEnable(GL_DEPTH_TEST);
}

int GraphicRenderer::renderCircles(const std::vector<RigidBody>& particles) {

	//CONVERT PARTICLES TO CIRCLE
	particleToCube(particles);
	const unsigned int nb_points = static_cast<unsigned int>(fvertices.size());

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, nb_points * sizeof(float), fvertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// render loop
	// -----------
	if (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// transformations
		// ---------------
		// create transformations
		// We first initialize each matrix to the identity matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		// the we apply our transformations
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -zoom));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		RigidBody rb = particles[0];
		Vector3D pos = rb.getPos().normalize();
		std::cout << rb.getOrientation() << std::endl;
		Matrix3 m = rb.getTransform();
		std::cout << m[0] << " " << m[1] << " " << m[2] << " " << 0 << " " << m[3] << " " << m[4] << " " << m[5] << " " << 0 << " " << m[6] << " " << m[7] << " " << m[8] << " " << std::endl;
		glm::mat4 model = glm::mat4(m[0], m[1], m[2], 0, m[3], m[4], m[5], 0, m[6], m[7], m[8], 0, 0, 0, 0, 1);
		//model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
		//model = glm::rotate(model, 3.0f, glm::vec3(1.0f,0, 0));

		//we retrieve the matrix uniform locations
		unsigned int modelLocation = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewLocation = glGetUniformLocation(shaderProgram, "view");
		unsigned int projectionLocation = glGetUniformLocation(shaderProgram, "projection");

		//then we pass each matrix into our shader
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw triangles
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, nb_points); 


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		return 0;
	}
	else {
		glfwTerminate();
		return 1;
	}
	
}

//turn a vector of particle into vertices to render as a cube composed of triangles
//return 0 if everything is OK, 1 if the window should or have close
void GraphicRenderer::particleToCube(const std::vector<RigidBody>& particles) {
	fvertices.clear();
	for_each(particles.begin(), particles.end(), [this](const RigidBody& p) {
		/*float radius = static_cast<float>(p.getRadius());
		if (radius <= 0.001f) radius = 7; //taille negligeable
		float triangle_size = zoom*radius;//0.01f*radius;
		const Vector3D& Pos = p.getPos();
		float x = static_cast<float>(Pos.x) * 2 / SCR_WIDTH * zoom;
		float y = static_cast<float>(Pos.z) * 2 / SCR_HEIGHT * zoom;
		float triangle_size_x = triangle_size / SCR_WIDTH;
		float triangle_size_y = triangle_size / SCR_HEIGHT;
		//first vertex, top of the triangle
		fvertices.push_back(x);
		fvertices.push_back(y + triangle_size_y);
		fvertices.push_back(0.0);
		//bottom left
		fvertices.push_back(x - triangle_size_x);
		fvertices.push_back(y - triangle_size_y);
		fvertices.push_back(0.0);
		//bottom right
		fvertices.push_back(x + triangle_size_x);
		fvertices.push_back(y - triangle_size_y);
		fvertices.push_back(0.0);*/

		double a = 0.1;//p.getRadius(); //half-ridge of our cube
		Vector3D ref = p.getPos();

		Vector3D cubePoints[4];
		cubePoints[0] = Vector3D(-a, -a, a);
		cubePoints[1] = Vector3D(-a, a, -a);
		cubePoints[2] = Vector3D(a, a, a);
		cubePoints[3] = Vector3D(a, -a, -a);
		for (int j = 0; j < 4; j++) {
			Vector3D& firstPoint = cubePoints[j];
			for (int i = 0; i < 3; i++) {
				Vector3D point2 = firstPoint;
				Vector3D point3 = point2 + ref;
				fvertices.push_back(static_cast<float>(point3.x));
				fvertices.push_back(static_cast<float>(point3.y));
				fvertices.push_back(static_cast<float>(point3.z));

				point2[(i + 1)% 3] *= -1;
				point3 = point2 + ref;
				fvertices.push_back(static_cast<float>(point3.x));
				fvertices.push_back(static_cast<float>(point3.y));
				fvertices.push_back(static_cast<float>(point3.z));

				point2[(i + 1) % 3] *= -1;
				point2[(i + 2) % 3] *= -1;
				point3 = point2 + ref;
				fvertices.push_back(static_cast<float>(point3.x));
				fvertices.push_back(static_cast<float>(point3.y));
				fvertices.push_back(static_cast<float>(point3.z));
			}
		}
	});

}

//Add a function to execute when key event detected
void GraphicRenderer::OnKeyEvent(std::function<void(std::string dir)> f) {
	callBackOnArrowKey.push_back(f);
}


