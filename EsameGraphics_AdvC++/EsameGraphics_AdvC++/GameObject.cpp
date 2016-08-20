#include "GameObject.h"
#include "glew.h"
#include "SystemManager.h"

void GameObject::initGameObject()
{
	velocity = vec3();
	angularVelocity = 0;
	mass = 1.0f;
	parent = nullptr;
	//collisionBehaviour = nullptr;
}

GameObject::GameObject()
{
	t.setToIdentity();
	initGameObject();
}

GameObject::GameObject(Transform t)
{
	setTransform(t);
	initGameObject();
}

void GameObject::setParent(GameObject * new_parent)
{
	this->parent = new_parent;
}

void GameObject::setCustomCollisionFunction(void(*customCollisionFunction)())
{
	this->customCollisionFunction = customCollisionFunction;
}

//void GameObject::setOnCollisionBehaviour(void(*collisionBehaviour)())
//{
//	this->collisionBehaviour = collisionBehaviour;
//}

void GameObject::setTransform(Transform t)
{
	this->t = t;
}

void GameObject::setPos(vec3 new_pos)
{
	t.setPos(new_pos);
}

vec3 GameObject::getPos() const
{
	return t.getPos();
}

vec3 GameObject::getGlobalPos() const
{
	GameObject* ancestor = parent;
	mat4 matrix = t.getModelMatrix();
	while (ancestor != nullptr)
	{
		matrix = ancestor->getTransform().getModelMatrix() * matrix;
		ancestor = ancestor->parent;
	}
	return vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
}

void GameObject::setScale(float new_scale)
{
	t.setScale(new_scale);
}

void GameObject::setVelocity(vec3 new_velocity)
{
	velocity = new_velocity;
}

void GameObject::setAngularVelocity(float new_angularVelocity)
{
	angularVelocity = new_angularVelocity;
}

void GameObject::setMass(float new_mass)
{
	mass = new_mass;
}

void GameObject::setCollider(Collider new_collider)
{
	collider = new_collider;
}

float GameObject::getScale() const
{
	return t.getScale();
}

float GameObject::getGlobalScale() const
{
	GameObject* ancestor = parent;
	float globalScale = t.getScale();
	while (ancestor != nullptr)
	{
		globalScale *= ancestor->getTransform().getScale();
		ancestor = ancestor->parent;
	}
	return globalScale;
}

vec3 GameObject::getVelocity() const
{
	return velocity;
}

float GameObject::getAngularVelocity() const
{
	return angularVelocity;
}

float GameObject::getMass() const
{
	return mass;
}

Collider GameObject::getCollider() const
{
	return collider;
}

GameObject * GameObject::getParent() const
{
	return parent;
}

void GameObject::translate(vec3 vector)
{
	t.translate(vector);
}

Transform GameObject::getTransform() const
{
	return t;
}

void GameObject::doRenderingStep()
{
	glPushMatrix();
	GameObject* ancestor = parent;
	mat4 matrix = t.getModelMatrix();
	while (ancestor != nullptr)
	{
		matrix = ancestor->getTransform().getModelMatrix() * matrix;
		ancestor = ancestor->parent;
	}
	glMultMatrixf(&(matrix[0][0]));
	render();
	glPopMatrix();
}

void GameObject::onCollision(GameObject * other)
{
	if (customCollisionFunction != nullptr) customCollisionFunction();
}
