#pragma once
#include "SDL.h"

enum Keys
{
	LEFT, RIGHT, MIX, START_GAME, N_KEYS
};

class InputManager
{
private:
	InputManager() {
		statusChanged = false;
		for (int i = 0; i < N_KEYS; i++)
		{
			status[i] = false;
		}
	};

public:
	static InputManager& getInstance();

	bool status[N_KEYS];
	bool statusChanged;
	void manageInput();

	static void processKey(SDL_Event& e, bool down);
};

