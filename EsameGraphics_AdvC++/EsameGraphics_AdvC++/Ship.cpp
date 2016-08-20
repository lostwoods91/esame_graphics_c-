#include "Ship.h"
#include "glew.h"
#include "SystemManager.h"
#include "GameManager.h"

const float Ship::length = 2.0f;
const float Ship::thickness = 0.2f;

void Ship::init()
{
	color = vec3(0.5f, 0.5f, 0.5f);

}

void Ship::render() const
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_QUADS);
	glVertex2f(-length / 2, thickness / 2);
	glVertex2f(length / 2, thickness / 2);
	glVertex2f(length / 2, -thickness / 2);
	glVertex2f(-length / 2, -thickness / 2);
	glEnd();
}

Ship::Ship()
{
	init();
}

Ship::Ship(Transform t) : GameObject(t)
{
	init();
}

Ship::Ship(Transform t, vec3 color) : GameObject(t)
{
	init();
	this->color = color;
}

void Ship::setColor(vec3 new_color)
{
	this->color = new_color;
}

float Ship::getLength() const
{
	return length * getScale();
}

float Ship::getThickness() const
{
	return thickness * getScale();
}

void Ship::onCollision(GameObject * other)
{
	float half_size = length * getGlobalScale() / 2;
	float hit_distance_from_center = glm::abs(other->getPos().x - getPos().x);
	float deviation_percentage = hit_distance_from_center / half_size;
	deviation_percentage = glm::clamp(deviation_percentage, 0.0f, 1.0f);
	GameManager::getInstance().onBallHit(deviation_percentage);
}

void Ship::doPhysicStep()
{
	t.translate(velocity * SystemManager::dt);

	if (getPos().x - getLength() / 2 < 0)
	{
		setPos(vec3(getLength() / 2, getPos().y, getPos().z));
	}
	else if (getPos().x + getLength() / 2 > SystemManager::viewport_size)
	{
		setPos(vec3(SystemManager::viewport_size - getLength() / 2, getPos().y, getPos().z));
	}
}

