#pragma once
#include <vector>
#include "WindowGL.h"

class WindowGLManager
{
public:
	static void addWindowGL(WindowGL* window);
	static void mainLoop();
	WindowGLManager();
	~WindowGLManager();
	static int isLooping;
private:
	static std::vector<WindowGL*> windowGLList;
	
};

