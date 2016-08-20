#pragma once
#include "GameObject.h"

// in model space, a ship is a rectangle of dimensions length x thickness
class Ship : public GameObject
{
private:
	vec3 color;
	void init();

	static const float length;
	static const float thickness;

protected:
	virtual void render() const;
public:
	Ship();
	Ship(Transform t);
	Ship(Transform t, vec3 color);

	void setColor(vec3 new_color);

	float getLength() const;
	float getThickness() const;

	virtual void onCollision(GameObject* other);
	virtual void doPhysicStep();
};

