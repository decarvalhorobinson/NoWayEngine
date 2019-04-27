#pragma once
#include "MouseListener.h"
#include "MouseEvent.h"
#include "KeyListener.h"
#include "KeyEvent.h"
#include "Component.h"
#include <vector>
class Container : public Component
{
private:
	std::vector<Component*> components;
public:
	Container();
	~Container();

	virtual void add(Component *component);
	//override
	virtual void processMouseEvent(MouseEvent *mouseEvent);
	virtual void processKeyEvent(KeyEvent *keyEvent);
	virtual bool isComponentAdded(Component *component);
	virtual void paintComponents(Graphics *pen);
	virtual void paint(Graphics *pen);


};

