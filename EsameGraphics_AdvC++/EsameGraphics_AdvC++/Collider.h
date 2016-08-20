#pragma once

enum Collider_Type
{
	NO_COLLIDER,
	SPHERE,
	RECTANGLE,
	N_COLLIDER_TYPES
};

class Collider
{
private:
	Collider_Type type;
	float radius;
	float width;
	float height;
	bool alive;

public:
	Collider();
	Collider(float radius);
	Collider(float width, float height);

	void setAlive(bool value);

	float getRadius() const;
	float getWidth() const;
	float getHeight() const;
	bool isAlive() const;
	Collider_Type getType() const;
};

