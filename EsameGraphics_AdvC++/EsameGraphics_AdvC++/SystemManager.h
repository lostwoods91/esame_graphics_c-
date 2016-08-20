#pragma once
#include "SDL.h"

class SystemManager
{
private:
	SystemManager() {};

public:
	SystemManager(SystemManager const&) = delete;
	void operator=(SystemManager const&) = delete;
	static SystemManager& getInstance();

	static const float viewport_size;
	static const int FPS;
	static const int PHYSICS_CYCLES_PER_FRAME;
	static const float dt;

	static void exit();
};