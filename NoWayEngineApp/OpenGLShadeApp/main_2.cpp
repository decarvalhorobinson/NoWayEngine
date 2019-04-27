#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "ShaderLoader.h"
#include "Grid.h"
#include "WindowGL.h"
#include "Camera.h"

#define WIDTH 640
#define HEIGHT 480

glm::vec3 cameraPos = glm::vec3(13.0f, 9.0f, 12.0f);
glm::vec3 cameraFront = glm::vec3(-0.6f, -0.6f, -0.6f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
GLfloat fov = 45.0f;
bool keys[1024];


//camera
GLfloat posX = 13.0f;
GLfloat posY = 9.0f;
GLfloat posZ = 12.0f;
GLfloat upX = 0.0f;
GLfloat upY = 1.0f;
GLfloat upZ = 0.0f;
GLfloat yaw = 0.0f;
GLfloat pitch = -90.0f;
Camera cam(posX, posY, posZ, upX, upY, upZ, yaw, pitch);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
bool firstMouse = true;
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	cam.processMouseMovement(xoffset, yoffset);
}

int main2() {
	

	Grid grid;
	//WindowGL windowsGl(640, 480, "Janela Custom", NULL, NULL);;

	//Projection initialization




	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	// uncomment these lines if on Apple OS X
	/*glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Window", NULL, NULL);
	glfwSetCursorPos(window, lastX, lastY);

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	//mouse input callback settings
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	//GLFWwindow* window2 = windowsGl.getWindow();
	//glfwMakeContextCurrent(window2);

	/* OTHER STUFF GOES HERE NEXT */
	////////
	float points[] = {
		0.0f,  1.5f,  0.0f,
		1.5f, 0.0f,  0.0f,
		-1.5f, 0.0f,  0.0f,
		0.0f,  1.5f,  1.0f,
		1.5f, 0.0f,  1.0f,
		-1.5f, 0.0f,  1.0f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * 2 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	ShaderLoader shaderLoader;
	GLuint bodeShaderProgram = shaderLoader.createShaderProgram("vertex.glsl", "fragment.glsl");
	GLuint bodeShaderColorProgram = shaderLoader.createShaderProgram("vertex_color.glsl", "fragment_color.glsl");

	
	while (!glfwWindowShouldClose(window)) {
		glfwMakeContextCurrent(window);
		glClearColor(0.7f, 0.71f, 0.72f, 1.0f);
		//View initialization
		GLfloat radius = 100.20f;
		GLfloat camX = sin(glfwGetTime()) * radius;
		GLfloat camY = cos(glfwGetTime()) * radius;
		GLfloat rot = glfwGetTime() * 100;
		rot = glm::radians(rot);
		rot = (int)(rot * 100) % (int)(6.28f * 100);
		rot = rot / 100;
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0.0f,0.0f,0.0f), cameraUp);

		
		// Projection 
		glm::mat4 projection;
		projection = glm::perspective(70.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.01f, 10000.0f);

		//Model transformations

		glm::mat4 model = glm::mat4(1.0f);
		model *= glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model *= glm::rotate(model, rot , glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 ModelViewMatrix = cam.getViewMatrix() * model;
		glm::mat4 ModelViewProjectionMatrix = projection * ModelViewMatrix;

				// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		


		glUseProgram(bodeShaderColorProgram);
		//glUniformMatrix4fv(glGetUniformLocation(bodeShaderColorProgram, "ModelView"), 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
		glUniformMatrix4fv(glGetUniformLocation(bodeShaderColorProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));

		grid.paint(bodeShaderColorProgram);

		glUseProgram(bodeShaderColorProgram);
		//glUniformMatrix4fv(glGetUniformLocation(bodeShaderProgram, "ModelView"), 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
		glUniformMatrix4fv(glGetUniformLocation(bodeShaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);

	
		
		// update other events like input handling 
		glfwPollEvents();

		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);

	}
	/////////////////
	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}