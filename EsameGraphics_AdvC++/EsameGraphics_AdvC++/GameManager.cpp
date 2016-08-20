#include "GameManager.h"
#include "glew.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "Ship.h"
#include "Block.h"
#include "SystemManager.h"
#include "Grid.h"
#include "TextureManager.h"
#include <iostream>

// SHIP SETTINGS
const float GameManager::ship_heightOfFlight = SystemManager::viewport_size / 10;
const float GameManager::ship_size = 1.5f;
const float GameManager::ship_speed = 5.0f;
const vec3 GameManager::ship_color = vec3(0, 0, 0);

// BALL SETTINGS
const float GameManager::ball_size = 0.4f;
const float GameManager::ball_speed = 5.0f;
const float HALF_PI = glm::half_pi<float>();
const float GameManager::ball_min_inclination = HALF_PI * 0.1f;
const float GameManager::ball_max_inclination = HALF_PI * 0.9f;

// GRID SETTINGS
const int GameManager::grid_rows = 5;
const int GameManager::grid_cols = 8;
const float GameManager::grid_size = 1.2f;
const float GameManager::grid_horizontal_pos = 0.5f;
const float GameManager::grid_vertical_pos = 0.1f;

// BACKGROUND SETTINGS
const vec3 GameManager::background_color = vec3(0.6f, 0.6f, 0.6f);

void lowerWallLoseFunction()
{
	GameManager::getInstance().onLose();
}

void GameManager::initGame()
{
	// GENERATE WALLS

	Collider collider_horizontalWall(SystemManager::viewport_size, 0);
	Collider collider_verticalWall(0, SystemManager::viewport_size);

	lefterWall = new GameObject(Transform(vec3(0, SystemManager::viewport_size / 2, 0),
		quat(1, 0, 0, 0), 1.0f));
	lefterWall->setCollider(collider_verticalWall);
	PhysicsEngine::getInstance().registerCollidableObject(lefterWall);

	righterWall = new GameObject(Transform(vec3(SystemManager::viewport_size, SystemManager::viewport_size / 2, 0),
		quat(1, 0, 0, 0), 1.0f));
	righterWall->setCollider(collider_verticalWall);
	PhysicsEngine::getInstance().registerCollidableObject(righterWall);

	upperWall = new GameObject(Transform(vec3(SystemManager::viewport_size / 2, SystemManager::viewport_size, 0),
		quat(1, 0, 0, 0), 1.0f));
	upperWall->setCollider(collider_horizontalWall);
	PhysicsEngine::getInstance().registerCollidableObject(upperWall);

	lowerWall = new GameObject(Transform(vec3(SystemManager::viewport_size / 2, 0, 0),
		quat(1, 0, 0, 0), 1.0f));
	lowerWall->setCollider(collider_horizontalWall);
	lowerWall->setCustomCollisionFunction(lowerWallLoseFunction);
	PhysicsEngine::getInstance().registerCollidableObject(lowerWall);

	// GENERATE SHIP

	ship = new Ship();
	ship->setScale(ship_size);
	ship->setColor(ship_color);
	ship->setCollider(Collider(ship->getLength(), ship->getThickness()));
	RenderingEngine::getInstance().registerRenderObject(ship);
	PhysicsEngine::getInstance().registerMovableObject(ship);
	PhysicsEngine::getInstance().registerCollidableObject(ship);

	// GENERATE BALL

	ball = new Ball();
	ball->setScale(ball_size);
	ball->setCollider(Collider(ball->getRadius()));
	RenderingEngine::getInstance().registerRenderObject(ball);
	PhysicsEngine::getInstance().registerMovableObject(ball);
	PhysicsEngine::getInstance().registerCollidableObject(ball);

	// GENERATE GRID

	grid = new Grid(grid_rows, grid_cols);
	grid->setScale(grid_size);
	const float grid_x = (SystemManager::viewport_size - grid->getWidth()) * grid_horizontal_pos;
	const float grid_y = SystemManager::viewport_size - (SystemManager::viewport_size - grid->getHeight()) * grid_vertical_pos;
	grid->setPos(vec3(grid_x, grid_y, 0));
	RenderingEngine::getInstance().registerRenderObject(grid);

	resetGame();
}

void GameManager::resetGame()
{
	PhysicsEngine::getInstance().disable();
	ball->setIdleness(true);
	ship->setPos(vec3(SystemManager::viewport_size / 2, ship_heightOfFlight, 0));
	ball->setPos(vec3(SystemManager::viewport_size / 2, ship_heightOfFlight + ball->getRadius() + ship->getThickness() / 2, 0));
	ship->setVelocity(vec3(0, 0, 0));
	ball->setVelocity(vec3(0, 0, 0));
	ball->setAngularVelocity(0);
	grid->generateRandomGrid();
	PhysicsEngine::getInstance().enable();
	std::cout << "Per vincere, distruggi tutti i " << grid->getNumberOfAliveBlocks() << " mattoncini!" << std::endl;
}

void GameManager::startGame()
{
	if (ball->isIdle())
	{
		ball->setIdleness(false);
		ball->setVelocity(vec3(1, 1, 0) * ball_speed);
	}
}

GameManager& GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}

Grid * GameManager::getGrid()
{
	return grid;
}

Ship * GameManager::getShip()
{
	return ship;
}

void GameManager::moveShipLeft()
{
	ship->setVelocity(vec3(-1, 0, 0) * ship_speed);
	if (ball->isIdle())
	{
		ball->setVelocity(vec3(-1, 0, 0) * ship_speed);
	}
}

void GameManager::moveShipRight()
{
	ship->setVelocity(vec3(1, 0, 0) * ship_speed);
	if (ball->isIdle())
	{
		ball->setVelocity(vec3(1, 0, 0) * ship_speed);
	}
}

void GameManager::stopShip()
{
	ship->setVelocity(vec3(0, 0, 0));
	if (ball->isIdle())
	{
		ball->setVelocity(vec3(0, 0, 0));
	}
}

void GameManager::changeBlocksDisposition()
{
	if (ball->isIdle())
	{
		grid->changeBlocksDisposition();
	}
}

void GameManager::onBallHit(float deviation)
{
	float angle = (ball_max_inclination - ball_min_inclination) * (1 - deviation) + ball_min_inclination;
	float magnitude = glm::length(ball->getVelocity());
	float x_dev = magnitude * glm::sign(ball->getVelocity().x) * glm::cos(angle);
	float y_dev = magnitude * glm::sign(ball->getVelocity().y) * glm::sin(angle);
	ball->setVelocity(vec3(x_dev, y_dev, 0));
	ball->setAngularVelocity(-glm::sign(ball->getVelocity().x) * deviation * HALF_PI * 4);
}

void GameManager::onWin()
{
	ball->setVelocity(vec3(0, 0, 0));
	std::cout << "Hai vinto!" << std::endl;
}

void GameManager::onLose()
{
	std::cout << "Hai perso... ritenta!" << std::endl;
	resetGame();
}
