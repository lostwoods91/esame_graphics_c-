#include "InputManager.h"
#include "GameManager.h"
#include "SystemManager.h"

InputManager & InputManager::getInstance()
{
	static InputManager instance;
	return instance;
}

void InputManager::processKey(SDL_Event & e, bool down)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		SystemManager::exit();
		break;
	case SDLK_n:
		if (!down) GameManager::getInstance().changeBlocksDisposition();
		//getInstance().status[MIX] = down ? true : false;
		//getInstance().statusChanged = true;
		break;
	case SDLK_LEFT:
		//GameManager::getInstance().moveShipLeft();
		getInstance().status[LEFT] = down ? true : false;
		getInstance().statusChanged = true;
		break;
	case SDLK_RIGHT:
		//GameManager::getInstance().moveShipRight();
		getInstance().status[RIGHT] = down ? true : false;
		getInstance().statusChanged = true;
		break;
	case SDLK_SPACE:
		if (!down) GameManager::getInstance().startGame();
		//getInstance().status[START_GAME] = down ? true : false;
		//getInstance().statusChanged = true;
		break;

	}
}

void InputManager::manageInput()
{
	if (status[LEFT])
		GameManager::getInstance().moveShipLeft();
	else if (status[RIGHT])
		GameManager::getInstance().moveShipRight();
	else
		GameManager::getInstance().stopShip();

}
