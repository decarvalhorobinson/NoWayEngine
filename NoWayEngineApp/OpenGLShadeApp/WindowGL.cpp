#include "WindowGL.h"
#include "WindowGLManager.h"
#include <stdio.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Grid.h"
#include "ShaderLoader.h"



#define WIDTH 800
#define HEIGHT 600


void WindowGL::init(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	//keep track os the window ID
	this->id = this->count;
	this->count++;

	// Set variables for the window
	this->width = width;
	this->height = height;
	this->title = title;

	//Initialize openGl GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize openGL.";
		exit(EXIT_FAILURE);
	}
	// Create the window
	window = glfwCreateWindow(this->width, this->height, this->title, monitor, share);
	//set a pointer to track the events for each window - static function solution
	glfwSetWindowUserPointer(window, this);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(this->swapInterval);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, this->width, this->height);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);

	//input callback settings
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetCursorPos(window,(GLfloat)width/ (GLfloat)2, (GLfloat)height / (GLfloat)2);
	glfwSetKeyCallback(window, keyCallBack);
	glfwSetScrollCallback(window, scrollCallback);

	//reset the key array for the callback input keyboard
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = false;
	}
	// shader program used on the grid
	ShaderLoader shaderLoader;
	this->gridShaderProgram = shaderLoader.createShaderProgram("vertex_color.glsl", "fragment_color.glsl");

}


WindowGL::WindowGL(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share){
	init(width, height, title, monitor, share);
	activeCam = new Camera();
	cameras.push_back(activeCam);

	Object newObj;
	newObj.loadMeshFromFile("farm_house.txt");
	newObj.loadShaderProgramFromFile("vertex.glsl", "fragment.glsl");

	Transformation transformation;
	transformation.position = glm::vec3(0, 0, 0);
	transformation.scale = glm::vec3(0.5, 0.5, 0.5);
	transformation.rotation = glm::vec3(0, 90, 0);
	newObj.setTransformation(transformation);
	objectMap["teste"] = newObj;
	//objectMap.erase(objectMap.find("teste"));
	objectMap["Caralho"] = objectMap["teste"];
	objectMap.erase(objectMap.find("teste"));
		
}


int WindowGL::getWidth(){
	return this->width;
}

void WindowGL::setWidth(int width){
	this->width = width;
}

int WindowGL::getHeight(){
	return height;
}

void WindowGL::setHeight(int height){
	this->height = height;
}

GLFWwindow * WindowGL::getWindow()
{
	return window;
}

void WindowGL::setTitle(char * title)
{
	glfwSetWindowTitle(getWindow(), title);
}

void WindowGL::mouseCallback(GLFWwindow * window, double xpos, double ypos)
{
	WindowGL * windowGL = reinterpret_cast<WindowGL *>(glfwGetWindowUserPointer(window));
	windowGL->mouseHandler(window, xpos, ypos);
}

void WindowGL::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	WindowGL * windowGL = reinterpret_cast<WindowGL *>(glfwGetWindowUserPointer(window));
	windowGL->keyHandler(window, key, scancode, action, mode);
}

void WindowGL::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	WindowGL * windowGL = reinterpret_cast<WindowGL *>(glfwGetWindowUserPointer(window));
	windowGL->scrollHandler(window, xoffset, yoffset);
	
}


void WindowGL::move(GLfloat deltaTime)
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		activeCam->processKeyboard(activeCam->FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		activeCam->processKeyboard(activeCam->BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		activeCam->processKeyboard(activeCam->LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		activeCam->processKeyboard(activeCam->RIGHT, deltaTime);
	if (keys[GLFW_KEY_LEFT_SHIFT])
		activeCam->processKeyboard(activeCam->TOP, deltaTime);
	if (keys[GLFW_KEY_SPACE])
		activeCam->processKeyboard(activeCam->DOWN, deltaTime);
}

void WindowGL::setActiveCam(Camera * cam)
{
	this->activeCam = cam;
}

void WindowGL::setErrorCallback()
{
	fputs("An error occurred ", stderr);

}


void WindowGL::mouseHandler(GLFWwindow * window, double xpos, double ypos)
{
	
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

	activeCam->processMouseMovement(xoffset, yoffset);

}

void WindowGL::keyHandler(GLFWwindow * window, int key, int scancode, int action, int mode)
{
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

void WindowGL::scrollHandler(GLFWwindow * window, double xoffset, double yoffset)
{
	activeCam->processMouseScroll(yoffset);
}



void WindowGL::render()
{
	glfwMakeContextCurrent(window);
	// Set frame time/Delta time
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	//move the camera to the direction of the movement according to delta time
	move(deltaTime);

	// Change the background color and clear the buffer
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Projection 
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(activeCam->getFieldOfView()), (GLfloat)width / (GLfloat)height, 0.01f, 10000.0f);
	// get the camera perspective view
	glm::mat4 view = activeCam->getViewMatrix();
	// get the object model matrix
	glm::mat4 model;
	//reset normal matrix

	glm::mat3 normalMatrix = glm::mat3(1.0f);
	//direction light/diffuse light
	glm::vec3  lightDirection = glm::normalize(activeCam->getTarget());
	glm::mat4 modelViewMatrix;
	GLuint shaderProgram;

	
	for (auto const &obj : objectMap) 
	{
		Object object = objectMap[obj.first];

		normalMatrix = glm::mat3(1.0f);
		model = object.getModelMatrix();
		model = glm::rotate(model, currentFrame, glm::vec3(0, 1, 0));
		modelViewMatrix = view * model;
		shaderProgram = object.getShaderProgram();
		normalMatrix *= glm::mat3(model);
		
		glUseProgram(shaderProgram);

			glUniform3fv(glGetUniformLocation(shaderProgram, "lightDirection"), 1, glm::value_ptr(lightDirection));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, 0, glm::value_ptr(projectionMatrix));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelViewMatrix"), 1, 0, glm::value_ptr(modelViewMatrix));
			glUniformMatrix3fv(glGetUniformLocation(shaderProgram, "normalMatrix"), 1, 0, glm::value_ptr(normalMatrix));

			object.render(shaderProgram);


		glUseProgram(0);

	}


	
	glUseProgram(gridShaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(gridShaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(projectionMatrix * view));
		glUniform3fv(glGetUniformLocation(gridShaderProgram, "VertexColor"), 1, glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f)));
		grid.paint(gridShaderProgram);
	glUseProgram(0);
	
	// update other events like input handling 
	glfwPollEvents();

	// put the stuff we've been drawing onto the display
	glfwSwapBuffers(window);



}




WindowGL::~WindowGL(){
}



Camera* WindowGL::getActiveCam()
{
	return activeCam;
}

int WindowGL::count;