#pragma once
class MouseEvent
{
private:
	float x;
	float y;
	float xOnScreen;
	float yOnScreen;
	int button;
	int action;
	int mods;
	bool entered;

public:
	MouseEvent(float x, float y, float xOnScreen, float yOnScreen, int button, int action, int mods)
		: x(x), y(y), xOnScreen(xOnScreen), yOnScreen(yOnScreen), button(button), action(action), mods(mods) {};
	~MouseEvent() {};

	float getX() { return x; };
	void setX(float x) { this->x = x; };

	float getY() { return y; };
	void setY(float y) { this->y = y; };

	float getXOnScreen() { return xOnScreen; }
	void setXOnScreen(float xOnScreen) { this->xOnScreen = xOnScreen; };

	float getYOnScreen() { return yOnScreen; }
	void setYOnScreen(float yOnScreen) { this->yOnScreen = yOnScreen; };

	int getButton() { return button; };
	void setButton(int button) { this->button = button; }

	int getAction() { return action; };
	void setAction(int action) { this->action = action; }

	int getMods() { return mods; };
	void setMods(int mods) { this->mods = mods; }

	bool getEntered() { return entered; };
	void setEntered(bool entered) { this->entered = entered; }

	void clear() { x = 0; y = 0; xOnScreen = 0; yOnScreen = 0; button = 0; action = 0; mods = 0; entered = 0; };

};

