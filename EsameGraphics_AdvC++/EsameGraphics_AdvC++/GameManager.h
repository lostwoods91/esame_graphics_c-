#pragma once
#include "Grid.h"
#include "Ship.h"
#include "Ball.h"

class GameManager
{
private:
	GameManager() {};

	Grid* grid;
	Ship* ship;
	Ball* ball;

	GameObject* lefterWall;
	GameObject* righterWall;
	GameObject* upperWall;
	GameObject* lowerWall;

public:
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
	static GameManager& getInstance();

	void initGame();
	void resetGame();
	void startGame();
	Grid* getGrid();
	Ship* getShip();
	void moveShipLeft();
	void moveShipRight();
	void stopShip();
	void changeBlocksDisposition();
	void onBallHit(float deviation);

	void onWin();
	void onLose();

	static const float ship_heightOfFlight;
	static const float ship_size;
	static const float ship_speed;
	static const vec3 ship_color;
	static const float ball_size;
	static const float ball_speed;
	static const float ball_min_inclination;
	static const float ball_max_inclination;
	static const int grid_rows;
	static const int grid_cols;
	static const float grid_size;
	static const float grid_horizontal_pos;
	static const float grid_vertical_pos;
	static const vec3 background_color;
};

