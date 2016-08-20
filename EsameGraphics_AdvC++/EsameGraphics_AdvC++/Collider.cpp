#include "Collider.h"



Collider::Collider()
{
	type = NO_COLLIDER;
	alive = true;
}

Collider::Collider(float radius)
{
	type = SPHERE;
	this->radius = radius;
	width = 0;
	height = 0;
	alive = true;
}

Collider::Collider(float width, float height)
{
	type = RECTANGLE;
	radius = 0;
	this->width = width;
	this->height = height;
	alive = true;
}

void Collider::setAlive(bool value)
{
	alive = value;
}

float Collider::getRadius() const
{
	return radius;
}

float Collider::getWidth() const
{
	return width;
}

float Collider::getHeight() const
{
	return height;
}

bool Collider::isAlive() const
{
	return alive;
}

Collider_Type Collider::getType() const
{
	return type;
}
