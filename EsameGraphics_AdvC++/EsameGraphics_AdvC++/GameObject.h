#pragma once
#include "Transform.h"
#include "Collider.h"

class GameObject
{
private:
	void initGameObject();

protected:
	Transform t;
	vec3 velocity;
	float angularVelocity;
	float mass;
	Collider collider;
	GameObject* parent;
	void(*customCollisionFunction)();

	virtual void render() const {};

public:
	GameObject();
	GameObject(Transform t);
	virtual ~GameObject() {};

	void setTransform(Transform t);
	void setPos(vec3 new_pos);
	void translate(vec3 vector);
	void setScale(float new_scale);
	void setVelocity(vec3 new_velocity);
	void setAngularVelocity(float new_angularVelocity);
	void setMass(float new_mass);
	void setCollider(Collider new_collider);
	void setParent(GameObject* new_parent);
	void setCustomCollisionFunction(void(*customCollisionFunction)());

	Transform getTransform() const;
	vec3 getPos() const;
	vec3 getGlobalPos() const;
	float getScale() const;
	float getGlobalScale() const;
	vec3 getVelocity() const;
	float getAngularVelocity() const;
	float getMass() const;
	Collider getCollider() const;
	GameObject* getParent() const;

	void doRenderingStep();
	virtual void onCollision(GameObject* other);
	virtual void doPhysicStep() {};
};

