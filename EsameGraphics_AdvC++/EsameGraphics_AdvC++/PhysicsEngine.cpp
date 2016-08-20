#include "PhysicsEngine.h"
#include "glm.hpp"

bool PhysicsEngine::checkCollision(GameObject * one, GameObject * two)
{
	Collider coll_one = one->getCollider();
	Collider coll_two = two->getCollider();

	if (coll_one.getType() == NO_COLLIDER || coll_two.getType() == NO_COLLIDER) return false;
	else if (coll_one.getType() == SPHERE && coll_two.getType() == SPHERE) return checkCollisionSS(one, two);
	else if (coll_one.getType() == RECTANGLE && coll_two.getType() == RECTANGLE) return checkCollisionRR(one, two);
	else if (coll_one.getType() == SPHERE && coll_two.getType() == RECTANGLE) return checkCollisionSR(one, two);
	else return checkCollisionSR(two, one);
}

bool PhysicsEngine::checkCollisionSS(GameObject * one, GameObject * two)
{
	// not implemented
	return false;
}

bool PhysicsEngine::checkCollisionRR(GameObject * one, GameObject * two)
{
	// not implemented
	return false;
}

// source: http://www.learnopengl.com/#!In-Practice/2D-Game/Collisions/Collision-Detection
bool PhysicsEngine::checkCollisionSR(GameObject * sphere, GameObject * rectangle)
{
	vec2 ball_center = sphere->getGlobalPos();
	vec2 rect_center = rectangle->getGlobalPos();
	float rect_half_width = rectangle->getCollider().getWidth() / 2;
	float rect_half_height = rectangle->getCollider().getHeight() / 2;
	vec2 half_extents(rect_half_width, rect_half_height);
	vec2 centers_dist = ball_center - rect_center;	// order is important!! distance vector is from rect to circle
	vec2 clamped_dist = glm::clamp(centers_dist, -half_extents, half_extents);
	vec2 rect_closestPointToCircle = rect_center + clamped_dist;
	vec2 ball_rect_dist = rect_closestPointToCircle - ball_center;
	return glm::length(ball_rect_dist) < sphere->getCollider().getRadius();
}

void PhysicsEngine::registerMovableObject(GameObject * gameObject)
{
	movableObjects.push_back(gameObject);
}

void PhysicsEngine::unregisterMovableObject(GameObject * gameObject)
{
	vector<GameObject*>::iterator it = movableObjects.begin();
	while (it < movableObjects.end() && *it != gameObject) ++it;
	if (it != movableObjects.end()) movableObjects.erase(it);
}

void PhysicsEngine::doPhysicsStep()
{
	for each (GameObject* object in movableObjects)
	{
		object->doPhysicStep();
	}
}

void PhysicsEngine::registerCollidableObject(GameObject * gameObject)
{
	collidableObjects.push_back(gameObject);
}

void PhysicsEngine::unregisterCollidableObject(GameObject * gameObject)
{
	vector<GameObject*>::iterator it = collidableObjects.begin();
	while (it < collidableObjects.end() && *it != gameObject) ++it;
	if (it != collidableObjects.end()) collidableObjects.erase(it);
}

const GameObject * PhysicsEngine::checkForCollisions(GameObject * gameObject)
{
	for each (GameObject* object in collidableObjects)
	{
		if (object != gameObject && object->getCollider().isAlive() && checkCollision(object, gameObject))
		{
			object->onCollision(gameObject);
			return object;
		}
	}
	return nullptr;
}

PhysicsEngine & PhysicsEngine::getInstance()
{
	static PhysicsEngine instance;
	return instance;
}
