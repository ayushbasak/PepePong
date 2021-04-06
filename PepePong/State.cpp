#include "State.h"

State::State()
{
	/*
	* State 0: Game Window - Start Menu
	* State 1: Game
	* State 2: Exit Window
	*/
	state = MENU;
}

State::State(int newState)
{
	state = newState;
}

int State::getState()
{
	return state;
}
