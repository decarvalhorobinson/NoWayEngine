#include "Component.h"
#include <iostream>

Component::Component()
{
	setBounds(0, 0, 0, 0);
}

Component::~Component()
{

}

void Component::setBounds(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

}

void Component::addMouseListener(MouseListener * mouseListener)
{
	mouseListeners.push_back(mouseListener);
}

void Component::addKeyListener(KeyListener * keyListener)
{
	keyListeners.push_back(keyListener);
}

void Component::processMouseEvent(MouseEvent * mouseEvent)
{
	MouseEvent * mouseEventInside = new MouseEvent(mouseEvent->getX(), mouseEvent->getY(),
		mouseEvent->getXOnScreen(), mouseEvent->getYOnScreen(), mouseEvent->getButton(), mouseEvent->getAction(), mouseEvent->getMods());
	if (!contains(mouseEventInside->getX(), mouseEventInside->getY())) return;
	mouseEventInside->setX((mouseEventInside->getX() - this->x));
	mouseEventInside->setY(mouseEventInside->getY() - this->y);
	for each (MouseListener *ml in mouseListeners)
	{
		ml->mousePressed(mouseEventInside);
		ml->mouseReleased(mouseEventInside);
		ml->mouseClicked(mouseEventInside);
		ml->mouseEntered(mouseEventInside);
		ml->mouseExited(mouseEventInside);
	}
	
}

void Component::processKeyEvent(KeyEvent * keyEvent)
{
	for each (KeyListener *kl in keyListeners)
	{
		kl->keyPressed(keyEvent);
		kl->keyReleased(keyEvent);
		kl->keyTyped(keyEvent);
	}
}

bool Component::contains(float x, float y)
{
	float opositeX = this->x + this->width;
	float opositeY = this->y + this->height;
	if((x >= this->x && x <= opositeX) &&
		(y >= this->y && y <= opositeY))
	{
		return true;
	}
	return false;
}

void Component::paint(Graphics *pen)
{
	pen->drawRectangle(this->x, this->y, this->width, this->height);
}
