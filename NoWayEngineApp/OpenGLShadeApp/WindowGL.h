#pragma once
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "Camera.h"
#include "Object.h"
#include "map"
#include "Grid.h"

class WindowGL
{
private:
	int width;
	int height;
	int id;
	char* title;
	GLfloat swapInterval = 1.0f;
	static int count;
	GLFWwindow* window;
	GLuint gridShaderProgram;
	GLfloat currentFrame = 0.0f;
	GLfloat deltaTime = 0.0f;
	Grid grid;
	Camera* activeCam;
	std::vector<Camera*> cameras;
	std::map<std::string, Object> objectMap;
public:
	WindowGL(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share);
	~WindowGL();
	void init(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share);
	int firstMouse = 1;
	GLfloat lastX = 640 / 2.0;
	GLfloat lastY = 480 / 2.0;
	bool keys[1024];
	GLfloat lastFrame = 0.0f;

	int getWidth();
	void setWidth(int width);
	int getHeight();
	void setHeight(int height);
	GLFWwindow* getWindow();
	void setErrorCallback();
	void mouseHandler(GLFWwindow * window, double xpos, double ypos);
	void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mode);
	void scrollHandler(GLFWwindow* window, double xoffset, double yoffset);

	void render();
	void setTitle(char* title);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void move(GLfloat deltaTime);
	void setActiveCam(Camera *cam);

	
	Camera* getActiveCam();

};

