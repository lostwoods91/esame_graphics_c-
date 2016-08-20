#include "Ball.h"
#include "glew.h"
#include "TextureManager.h"
#include "SystemManager.h"
#include "PhysicsEngine.h"

const float Ball::radius = 0.5f;
const float Ball::collision_spin = glm::pi<float>();

void Ball::bounce(const GameObject* other)
{
	float myX = t.getPos().x;
	float myY = t.getPos().y;
	float otherX = other->getGlobalPos().x;
	float otherY = other->getGlobalPos().y;

	bool bounceLEFT = myX < otherX - other->getCollider().getWidth() / 2;
	bool bounceRIGHT = myX > otherX + other->getCollider().getWidth() / 2;
	bool bounceDOWN = myY < otherY - other->getCollider().getHeight() / 2;
	bool bounceUP = myY > otherY + other->getCollider().getHeight() / 2;

	if (bounceLEFT)
	{
		// bounce LEFT
		velocity.x = -glm::abs(velocity.x);
		setPos(vec3(otherX - other->getCollider().getWidth() / 2 - collider.getRadius(), myY, 0));
	}
	if (bounceRIGHT)
	{
		// bounce RIGHT
		velocity.x = glm::abs(velocity.x);
		setPos(vec3(otherX + other->getCollider().getWidth() / 2 + collider.getRadius(), myY, 0));
	}
	if (bounceDOWN)
	{
		// bounce DOWN
		velocity.y = -glm::abs(velocity.y);
		setPos(vec3(myX, otherY - other->getCollider().getHeight() / 2 - collider.getRadius(), 0));
	}
	if (bounceUP)
	{
		// bounce UP
		velocity.y = glm::abs(velocity.y);
		setPos(vec3(myX, otherY + other->getCollider().getHeight() / 2 + collider.getRadius(), 0));
	}

	if (velocity.x < 0) angularVelocity += collision_spin;
	else angularVelocity -= collision_spin;
}

void Ball::render() const
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-radius, radius);
	glTexCoord2f(0.0, 1.0); glVertex2f(-radius, -radius);
	glTexCoord2f(1.0, 1.0); glVertex2f(radius, -radius);
	glTexCoord2f(1.0, 0.0); glVertex2f(radius, radius);
	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

Ball::Ball()
{
	textureID = TextureManager::getInstance().ball_texture;
}

Ball::Ball(Transform t) : GameObject(t)
{
	textureID = TextureManager::getInstance().ball_texture;
}

void Ball::setIdleness(bool idle)
{
	this->idle = idle;
	collider.setAlive(!idle);
}

bool Ball::isIdle() const
{
	return idle;
}

float Ball::getRadius() const
{
	return radius * getScale();
}

void Ball::doPhysicStep()
{
	t.translate(velocity * SystemManager::dt);
	t.rotate(angularVelocity * SystemManager::dt);

	if (idle)
	{
		if (getPos().x - getRadius() < 0)
		{
			setPos(vec3(getRadius(), getPos().y, getPos().z));
		}
		else if (getPos().x + getRadius() > SystemManager::viewport_size)
		{
			setPos(vec3(SystemManager::viewport_size - getRadius(), getPos().y, getPos().z));
		}
	}

	if (collider.isAlive())									// don't check for collisions if your collider isn't alive
	{
		const GameObject* collidedObject = PhysicsEngine::getInstance().checkForCollisions(this);
		if (collidedObject != nullptr)
		{
			if (collider.isAlive()) bounce(collidedObject);		// another check is necessary because the other object could have disabled your collider
		}
	}
}
