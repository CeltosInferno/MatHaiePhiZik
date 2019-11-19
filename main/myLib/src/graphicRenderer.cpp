#define _USE_MATH_DEFINES

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

int GraphicRenderer::renderCubes(const std::vector<RigidBody>& particles) {

	//CONVERT PARTICLES TO CIRCLE
	fvertices.clear();
	for each  (RigidBody RB in particles)
	{
		renderCubes(RB);
	}
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

		//managing model
		glm::mat4 model = glm::mat4(1.0f);

		//managing view
		glm::mat4 view = glm::mat4(1.0f);

		//managing projection
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

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


		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);

		glDrawArrays(GL_TRIANGLES,0, nb_points);
		
		
		 


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

void GraphicRenderer::addVectorToVertices(Vector3D v) {
	fvertices.push_back(v.x);
	fvertices.push_back(v.y);
	fvertices.push_back(v.z);
}

//turn a vector of particle into vertices to render as a cube composed of triangles
//return 0 if everything is OK, 1 if the window should or have close
void GraphicRenderer::renderCubes(RigidBody buddy) {

		double a = 0.1;
		
		//Translate Matrix
		Vector3D pos = buddy.getPos();
		Matrix4 ViewTranslate = Matrix4::TranslationOf(Vector3D(0, 0, -zoom));
		Matrix4 TranslateMat = Matrix4::TranslationOf(pos);
		Matrix4 RotationMat = buddy.getOrientation().toMatrix4();

		Matrix4 FinalM = ViewTranslate * TranslateMat * RotationMat;

		Vector3D cubePoints[8];
		cubePoints[0] = FinalM * Vector3D(-a, a, a);
		cubePoints[1] = FinalM * Vector3D(-a, a, -a);
		cubePoints[2] = FinalM * Vector3D(-a, -a, -a);
		cubePoints[3] = FinalM * Vector3D(-a, -a, a);
		cubePoints[4] = FinalM * Vector3D(a, a, a);
		cubePoints[5] = FinalM * Vector3D(a, a, -a);
		cubePoints[6] = FinalM * Vector3D(a, -a, -a);
		cubePoints[7] = FinalM * Vector3D(a, -a, a);


		//FACE ONE 2.3.6.7
		//3.6.7
		addVectorToVertices(cubePoints[3]);
		addVectorToVertices(cubePoints[6]);
		addVectorToVertices(cubePoints[7]);
		//3.6.2
		addVectorToVertices(cubePoints[3]);
		addVectorToVertices(cubePoints[6]);
		addVectorToVertices(cubePoints[2]);

		//FACE TWO 1.2.5.6
		//1.6.5
		addVectorToVertices(cubePoints[1]);
		addVectorToVertices(cubePoints[6]);
		addVectorToVertices(cubePoints[5]);
		//1.6.2
		addVectorToVertices(cubePoints[1]);
		addVectorToVertices(cubePoints[6]);
		addVectorToVertices(cubePoints[2]);

		//FACE THREE 0.1.2.3
		//0.2.3
		addVectorToVertices(cubePoints[0]);
		addVectorToVertices(cubePoints[2]);
		addVectorToVertices(cubePoints[3]);
		//0.2.1
		addVectorToVertices(cubePoints[0]);
		addVectorToVertices(cubePoints[2]);
		addVectorToVertices(cubePoints[1]);

		//FACE FOUR 0.1.4.5
		//0.5.1
		addVectorToVertices(cubePoints[0]);
		addVectorToVertices(cubePoints[1]);
		addVectorToVertices(cubePoints[5]);
		//0.5.4
		addVectorToVertices(cubePoints[0]);
		addVectorToVertices(cubePoints[5]);
		addVectorToVertices(cubePoints[4]);

		//FACE FIVE 4.5.6.7
		//4.6.5
		addVectorToVertices(cubePoints[4]);
		addVectorToVertices(cubePoints[6]);
		addVectorToVertices(cubePoints[5]);
		//4.6.7
		addVectorToVertices(cubePoints[4]);
		addVectorToVertices(cubePoints[6]);
		addVectorToVertices(cubePoints[7]);

		//FACE SIX 0.3.4.7
		//0.7.3
		addVectorToVertices(cubePoints[0]);
		addVectorToVertices(cubePoints[7]);
		addVectorToVertices(cubePoints[3]);
		//0.7.4
		addVectorToVertices(cubePoints[0]);
		addVectorToVertices(cubePoints[7]);
		addVectorToVertices(cubePoints[4]);
}

//Add a function to execute when key event detected
void GraphicRenderer::OnKeyEvent(std::function<void(std::string dir)> f) {
	callBackOnArrowKey.push_back(f);
}


