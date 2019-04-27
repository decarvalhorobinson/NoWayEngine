#include "WindowGLManager.h"
#include "WindowGL.h"




void WindowGLManager::addWindowGL(WindowGL* window)
{
	windowGLList.push_back(window);
}

void WindowGLManager::mainLoop() {
	isLooping = 1;
	while (isLooping) {
		if (windowGLList.size() <= 0) isLooping = 0;
		for (int it = 0; it < windowGLList.size(); ++it) {	
			WindowGL* windowGL = windowGLList[it];
			windowGL->render();
			if (glfwWindowShouldClose(windowGL->getWindow()) ){
				glfwHideWindow(windowGL->getWindow());
				windowGLList.erase(windowGLList.begin() + it);

			}

		}
		
	}
	glfwTerminate();
}

WindowGLManager::WindowGLManager(){
}


WindowGLManager::~WindowGLManager()
{
}


std::vector<WindowGL*> WindowGLManager::windowGLList;
int WindowGLManager::isLooping;