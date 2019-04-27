#include "WindowGLCustom.h"
#include "WindowGLManager.h"



void WindowGLCustom::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_SPACE) {
		WindowGL* window = new WindowGL(640, 480, "Dentro Custom Evento", NULL, NULL);
		WindowGLManager::addWindowGL(window);
	}

}

WindowGLCustom::WindowGLCustom(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share) 
	: WindowGL(width, height, title, monitor, share)
{
	glfwSetWindowTitle(getWindow(), "Custom Window");
	
}


WindowGLCustom::~WindowGLCustom()
{
}
