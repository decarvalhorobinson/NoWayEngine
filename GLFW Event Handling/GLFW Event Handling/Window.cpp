#include "Window.h"



Window::Window()
{

}


Window::~Window()
{
}

void Window::setContentPane(Container *container)
{
	this->container = container;
}

void Window::processKeyEvent(KeyEvent * keyEvent)
{
	container->processKeyEvent(keyEvent);
}

void Window::processMouseEvent(MouseEvent * mouseEvent)
{

	if (!contains(mouseEvent->getX(), mouseEvent->getY())) return;
	mouseEvent->setX(mouseEvent->getX() - this->getX());
	mouseEvent->setY(mouseEvent->getY() - this->getY());
	Container::processMouseEvent(mouseEvent);
	container->processMouseEvent(mouseEvent);
}

void Window::paint(Graphics * pen)
{
	Component::paint(pen);
	pen->setX(this->getX());
	pen->setY(this->getY());
	container->paint(pen);
}
