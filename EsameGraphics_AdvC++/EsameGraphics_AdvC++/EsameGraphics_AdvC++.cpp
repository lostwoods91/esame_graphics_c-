// EsameGraphics_AdvC++.cpp : definisce il punto di ingresso dell'applicazione console.
/*

Features opzionali integrate:

- l'utente muove la racchetta a dx e sx
- il gioco è giocatile, movimento racchetta, pallina e collisioni pallina
- si ha una sola possibilità poi il livello ricomincia
- non tutti i mattoncini si rompono al primo colpo, alcuni al secondo colpo.
- quando si rompono alcuni mattoncini viene dato un bonus

Features aggiuntive:

- la pallina ha una texture alphata e cambia velocità lineare e angolare quando collide
-

*/

#include "SDL.h"
#include <iostream>
#include "glew.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "GameManager.h"
#include "SystemManager.h"
#include "InputManager.h"
#include "TextureManager.h"
#include <time.h>

#define SDL_UPDATEEVENT SDL_USEREVENT	// custom event used for letting go ahead the main update cycle

bool quitGame = false;
SDL_Window *window;						// pointer to the main window
SDL_GLContext glcontext;				// main context

void update(SDL_Event& e)				// main update cycle
{
	static int nframe = 0;
	//std::cout << "Frame: " << nframe++ << std::endl;

	InputManager::getInstance().manageInput();

	for (int i = 0; i < SystemManager::PHYSICS_CYCLES_PER_FRAME; ++i)
	{
		if (PhysicsEngine::getInstance().isEnabled())
			PhysicsEngine::getInstance().doPhysicsStep();
	}

	if (RenderingEngine::getInstance().isEnabled())
		RenderingEngine::getInstance().doRenderingStep();

	SDL_GL_SwapWindow(window);
}

void processEvent(SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_QUIT:
		quitGame = true;
		break;
	case SDL_KEYDOWN:
		InputManager::getInstance().processKey(e, true);
		break;
	case SDL_KEYUP:
		InputManager::getInstance().processKey(e, false);
		break;
	case SDL_UPDATEEVENT:
		update(e);
		break;
	}
}

unsigned int pushUpdateEvent(unsigned int time, void* data)
{

	SDL_Event e;
	e.type = SDL_UPDATEEVENT;
	SDL_PushEvent(&e);
	return 1000 / SystemManager::FPS;
}

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);              // Initialize SDL2

															// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"Arkanoid",											// window title
		SDL_WINDOWPOS_UNDEFINED,							// initial x position
		SDL_WINDOWPOS_UNDEFINED,							// initial y position
		500,												// width, in pixels
		500,												// height, in pixels
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN				// flags - see below
		);

	glcontext = SDL_GL_CreateContext(window);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	// notify the system that he has to update every 1000 / FPS milliseconds
	SDL_AddTimer(1000 / SystemManager::FPS, pushUpdateEvent, nullptr);

	// init rendering
	RenderingEngine::initRendering();

	// load textures
	TextureManager::loadTextures();

	// init pseudo random number generator
	srand(time(NULL));

	// init game
	GameManager::getInstance().initGame();

	// start game!
	while (!quitGame)
	{
		SDL_Event ev;
		SDL_WaitEvent(&ev);
		processEvent(ev);
	}

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}