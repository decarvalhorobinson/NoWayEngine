#pragma once
class KeyEvent
{
private:
	int key;
	int scancode;
	int action;
	int mods;
public:
	KeyEvent(int key, int scancode, int action, int mods) : key(key), scancode(scancode), action(action), mods(mods) {};
	~KeyEvent() {};

	int getKey() { return key; };
	int getScancode() { return scancode; };
	int getAction() { return action; };
	int getMods() { return mods; };
};

