#pragma once
#include "WindowGL.h"
class WindowGLCustom :
	public WindowGL
{
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	WindowGLCustom(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share);
	~WindowGLCustom();
};

