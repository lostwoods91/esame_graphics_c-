#include "Transform.h"
#include "glew.h"
#include "SystemManager.h"

Transform::Transform()
{
	setToIdentity();
}

Transform::Transform(vec3 pos, quat ori, float scale)
{
	this->pos = pos;
	this->ori = ori;
	this->scale = scale;
}

void Transform::setToIdentity()
{
	pos = vec3(0, 0, 0);
	ori = quat(1, 0, 0, 0);
	scale = 1;
}

void Transform::setPos(vec3 new_pos)
{
	pos = new_pos;
}

void Transform::translate(vec3 vector)
{
	pos.x += vector.x;
	pos.y += vector.y;
	pos.z += vector.z;
}

void Transform::rotate(float angle)
{
	ori *= glm::angleAxis(angle, vec3(0, 0, 1));
	//ori *= glm::slerp(quat(1, 0, 0, 0), angle, SystemManager::dt);
}

vec3 Transform::forward() const
{
	quat tmp = ori * quat(0, 0, 1, 0) * conjugate(ori);
	return vec3(tmp.x, tmp.y, tmp.z);
}

mat4 Transform::getModelMatrix() const
{
	mat4 rotMat = glm::mat4_cast(ori);
	mat4 traMat;
	mat4 scaMat;
	scaMat[0][0] = scale;
	scaMat[1][1] = scale;
	scaMat[2][2] = scale;
	traMat[3] = vec4(pos, 1);
	mat4 m = traMat * rotMat * scaMat;
	return m;
}

vec3 Transform::getPos() const
{
	return pos;
}

void Transform::setScale(float new_scale)
{
	scale = new_scale;
}

void Transform::setOrientation(quat new_orientation)
{
	ori = new_orientation;
}

float Transform::getScale()  const
{
	return scale;
}

quat Transform::getOrientation() const
{
	return ori;
}
