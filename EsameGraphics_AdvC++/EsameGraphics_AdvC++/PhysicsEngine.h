#pragma once
#include <vector>
#include "GameObject.h"
using std::vector;

class PhysicsEngine
{
private:
	PhysicsEngine() { enabled = false; };

	bool enabled;

	vector<GameObject*> movableObjects;
	vector<GameObject*> collidableObjects;

	bool checkCollision(GameObject* one, GameObject* two);
	bool checkCollisionSS(GameObject* one, GameObject* two);
	bool checkCollisionRR(GameObject* one, GameObject* two);
	bool checkCollisionSR(GameObject* one, GameObject* two);

public:
	PhysicsEngine(PhysicsEngine const&) = delete;
	void operator=(PhysicsEngine const&) = delete;
	static PhysicsEngine& getInstance();

	void enable() { enabled = true; };
	void disable() { enabled = false; };
	bool isEnabled() { return enabled; };

	void registerMovableObject(GameObject* gameObject);
	void unregisterMovableObject(GameObject* gameObject);
	void doPhysicsStep();
	void registerCollidableObject(GameObject* gameObject);
	void unregisterCollidableObject(GameObject* gameObject);
	const GameObject* checkForCollisions(GameObject* gameObject);

};

