#pragma once
#define MENU 0
#define GAME 1
#define EXIT_GAME 2
class State
{
private:
	int state;

public:
	State();
	State(int newState);
	int getState();
	void setState(int newState);
};

