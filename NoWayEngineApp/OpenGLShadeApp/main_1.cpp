
#include <stdlib.h>
#include <stdio.h>
#include "WindowGL.h"
#include "WindowGLManager.h"
#include "WindowGLCustom.h"
#include <iostream>

int main(void)
{



	WindowGL*window3, *window4;
	WindowGLCustom* windowC5;

	//windowC5 = new WindowGLCustom(640, 480, "Janela Custom", NULL, NULL);
	window3 = new WindowGL(800, 600, "Janela 1", NULL, NULL);
	//window4 = new WindowGL(640, 480, "Janela 2", NULL, NULL);
	

	window3->setTitle("Janela 2");
	//window3->setTitle("Janela 1");
	// Set the required callback functions

	WindowGLManager::addWindowGL(window3);
	//WindowGLManager::addWindowGL(window4);
	//WindowGLManager::addWindowGL(windowC5);

	WindowGLManager::mainLoop();
	//window4->getHeight();
	
	return 0;

}
