#include "SystemManager.h"
#include "stb_image.h"

const float SystemManager::viewport_size = 10.0f;
const int SystemManager::FPS = 60;
const int SystemManager::PHYSICS_CYCLES_PER_FRAME = 2;
const float SystemManager::dt = 1.0f / FPS / PHYSICS_CYCLES_PER_FRAME;

SystemManager & SystemManager::getInstance()
{
	static SystemManager instance;
	return instance;
}

void SystemManager::exit()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}
