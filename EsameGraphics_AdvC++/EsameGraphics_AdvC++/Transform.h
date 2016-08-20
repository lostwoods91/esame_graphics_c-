#pragma once
#include "glm.hpp"
#include "gtc\quaternion.hpp"
using namespace glm;

class Transform
{
private:
	vec3 pos;
	quat ori;
	float scale;
public:
	Transform();
	Transform(vec3 pos, quat ori, float scale);

	void setToIdentity();
	void translate(vec3 vector);
	void rotate(float angle);
	void setPos(vec3 new_pos);
	void setScale(float new_scale);
	void setOrientation(quat new_orientation);

	vec3 forward() const;
	mat4 getModelMatrix() const;
	vec3 getPos() const;
	float getScale() const;
	quat getOrientation() const;
};

