#pragma once
#include "GameObject.h"
#include "glew.h"

// in model space, a ball is a square of edge radius * 2, with a texture applied on it
class Ball : public GameObject
{
private:
	bool idle;
	GLuint textureID;
	vec3 oldPos;

	static const float radius;
	static const float collision_spin;

	void bounce(const GameObject* other);

protected:
	virtual void render() const;

public:
	Ball();
	Ball(Transform t);

	void setIdleness(bool isIdle);
	bool isIdle() const;

	float getRadius() const;

	virtual void doPhysicStep();
};

