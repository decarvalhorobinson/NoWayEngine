#pragma once
#include "MouseEvent.h"
class MouseListener
{
private:

public:
	MouseListener() {};
	~MouseListener() {};

	virtual void mousePressed(MouseEvent *mouseEvent) = 0;
	virtual void mouseReleased(MouseEvent *mouseEvent) = 0;
	virtual void mouseEntered(MouseEvent *mouseEvent) = 0;
	virtual void mouseExited(MouseEvent *mouseEvent) = 0;
	virtual void mouseClicked(MouseEvent *mouseEvent) = 0;
};

