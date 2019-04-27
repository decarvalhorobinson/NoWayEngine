#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include "Container.h"
#include "KeyEvent.h"
#include "Component.h"
#include "MouseListener.h"
#include "MouseEvent.h"
#include <iostream>
#include "Window.h"
#include <fstream>
#include <string>
Window *windowEvt = new Window();
Container *container = new Container();
Container *containerInside = new Container();
Container *containerInsideInside = new Container();
Component *comp = new Component();
Component *comp2 = new Component();
class MyKeyListener : public KeyListener 
{
	void keyPressed(KeyEvent *keyEvent) { std::cout << "key = " << keyEvent->getKey() << "/ Action = " << keyEvent->getAction() << "/ Mods = " << keyEvent->getMods() << "\n";};
	void keyReleased(KeyEvent *keyEvent) { std::cout << "key = " << keyEvent->getKey() << "/ Action = " << keyEvent->getAction() << "/ Mods = " << keyEvent->getMods() << "\n";};
	void keyTyped(KeyEvent *keyEvent) { std::cout << "key = " << keyEvent->getKey() << "/ Action = " << keyEvent->getAction() << "/ Mods = " << keyEvent->getMods() << "\n";};
};
KeyListener *kl=  new MyKeyListener();
class MyKeyListener2 : public KeyListener
{
	void keyPressed(KeyEvent *keyEvent) { std::cout << "key2 = " << keyEvent->getKey() << "/ Action2 = " << keyEvent->getAction() << "/ Mods2 = " << keyEvent->getMods() << "\n"; };
	void keyReleased(KeyEvent *keyEvent) { std::cout << "key2 = " << keyEvent->getKey() << "/ Action2 = " << keyEvent->getAction() << "/ Mods2 = " << keyEvent->getMods() << "\n"; };
	void keyTyped(KeyEvent *keyEvent) { std::cout << "key2 = " << keyEvent->getKey() << "/ Action2 = " << keyEvent->getAction() << "/ Mods2 = " << keyEvent->getMods() << "\n"; };
};
KeyListener *kl2 = new MyKeyListener2();

class MyMouseListener : public MouseListener
{
	void mousePressed(MouseEvent *mouseEvent) {std::cout << "X value = " << mouseEvent->getX() << "/ Y value = " << mouseEvent->getY() << "\n"; };
	void mouseReleased(MouseEvent *mouseEvent) {};
	void mouseEntered(MouseEvent *mouseEvent) {};
	void mouseExited(MouseEvent *mouseEvent) {};
	void mouseClicked(MouseEvent *mouseEvent) {};
};
MouseListener *ml = new MyMouseListener();
MouseListener *ml2 = new MyMouseListener();
MouseListener *ml3 = new MyMouseListener();
MouseListener *ml4 = new MyMouseListener();
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//KeyEvent* keyEvent = new KeyEvent(key, scancode, action, mods);
	//windowEvt->processKeyEvent(keyEvent);

}
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	MouseEvent *mouseEvent = new MouseEvent((int)xpos, (int)ypos, 0, 0, 0, 0, 0);
	windowEvt->processMouseEvent(mouseEvent);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	
	double xpos;
	double ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	MouseEvent *mouseEvent = new MouseEvent((int)xpos, (int)ypos,0, 0, button, action, mods);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		
		windowEvt->processMouseEvent(mouseEvent);
	}
		
}



int main(void)
{
	//-----------------------
	// TEST AREA

	
	Graphics pen;
	containerInsideInside->setBounds(10, 10, 130, 100);
	containerInsideInside->addMouseListener(ml);

	comp->addMouseListener(ml2);
	comp->setBounds(5, 5.0, 30, 35);

	containerInside->add(comp);
	container->addMouseListener(ml3);
	containerInsideInside->add(comp);
	containerInside->addMouseListener(ml2);


	comp2->addMouseListener(ml4);
	comp2->setBounds(0, 100, 50, 60);
	containerInside->add(comp2);
	containerInside->add(containerInsideInside);
	containerInside->setBounds(20, 100, 250, 200);//
	container->add(containerInside);
	
	container->setBounds(100, 200, 300, 300);
	

	windowEvt->setContentPane(container);
	//----------------

	windowEvt->setBounds(0, 0, 500, 500);

	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);


	//initBuffers();
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		windowEvt->paint(&pen);	

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}