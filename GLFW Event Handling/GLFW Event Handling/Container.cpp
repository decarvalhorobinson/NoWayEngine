#include "Container.h"
#include <iostream>



Container::Container()
{
}


Container::~Container()
{	
}

void Container::add(Component *component)
{
	if(isComponentAdded(component)==true) return;
	components.push_back(component);
}

void Container::processKeyEvent(KeyEvent * keyEvent)
{
	Component::processKeyEvent(keyEvent);
	for each (Component *comp in components)
	{
		comp->processKeyEvent(keyEvent);
	}
}

bool Container::isComponentAdded(Component *component)
{
	return std::find(components.begin(), components.end(), component) != components.end();
}

void Container::paintComponents(Graphics * pen)
{
	
	pen->addX(this->getX());
	pen->addY(this->getY());
	for each (Component *comp in components)
	{
		comp->paint(pen);

	}
	pen->reset();
	
}

void Container::paint(Graphics * pen)
{	
	Component::paint(pen);
	paintComponents(pen);	
}

void Container::processMouseEvent(MouseEvent * mouseEvent)
{
	MouseEvent * mouseEventInside = new MouseEvent(mouseEvent->getX(), mouseEvent->getY(),
		mouseEvent->getXOnScreen(), mouseEvent->getYOnScreen(), mouseEvent->getButton(), mouseEvent->getAction(), mouseEvent->getMods());
	if(this->contains(mouseEventInside->getX(), mouseEventInside->getY()))
	{
		Component::processMouseEvent(mouseEventInside);
	}
	else
	{
		return;
	}
	mouseEventInside->setX(mouseEventInside->getX() - this->getX());
	mouseEventInside->setY(mouseEventInside->getY() - this->getY());
	for each (Component *comp in components)
	{
		if (!comp->contains(mouseEventInside->getX(), mouseEventInside->getY()))
		{
			continue;
		}
		else 
		{
			comp->processMouseEvent(mouseEventInside);
		}
		
	}
}