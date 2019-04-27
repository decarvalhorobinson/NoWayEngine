#pragma once
#include "KeyEvent.h"
class KeyListener
{
public:
	KeyListener() {};
	~KeyListener() {};

	virtual void keyPressed(KeyEvent *keyEvent) = 0;
	virtual void keyReleased(KeyEvent *keyEvent) = 0;
	virtual void keyTyped(KeyEvent *keyEvent) = 0;
};

