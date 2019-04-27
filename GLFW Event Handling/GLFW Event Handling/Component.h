#pragma once
#include <vector>
#include "MouseListener.h"
#include "KeyListener.h"
#include "Graphics.h"
#include <string>

class Component
{
private:
	std::vector<MouseListener*> mouseListeners;
	std::vector<KeyListener*> keyListeners;
	float width;
	float height;
	float x;
	float y;
	float z;
public:
	Component();
	~Component();
	std::string name;

	virtual void setBounds(float x, float y, float width, float height);
	virtual void addMouseListener(MouseListener *mouseListener);
	virtual void addKeyListener(KeyListener *keyListener);
	virtual void processMouseEvent(MouseEvent *mouseEvent);
	virtual void processKeyEvent(KeyEvent *keyEvent);
	virtual bool contains(float x, float y);
	virtual void paint(Graphics *pen);
	virtual float getX() { return x; };
	virtual void setX(float x) { this->x = x; };
	virtual float getY() { return y;};
	virtual void setY(float y) { this->y = y; };


};

