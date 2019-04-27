#pragma once
#include "Container.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
class Window : public Container
{
private:
	Container *container;
public:
	Window();
	~Window();
	virtual void setContentPane(Container *container) ;
	virtual void processKeyEvent(KeyEvent *keyEvent);
	virtual void processMouseEvent(MouseEvent *mouseEvent);
	void paint(Graphics *pen);
};

