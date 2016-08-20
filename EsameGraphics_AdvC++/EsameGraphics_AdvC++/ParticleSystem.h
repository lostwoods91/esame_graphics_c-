#pragma once
#include <vector>
#include <random>
#include "GameObject.h"

// source: https://github.com/SFML/SFML/wiki/Source:-Particle-System
class Randomizer {
public:
	Randomizer() : device_(), engine_(device_()) {};
	int rnd(int a, int b) {
		std::uniform_int_distribution<int> uni_dist(a, b);
		return uni_dist(engine_);
	};
	double rnd(double a, double b) {
		std::uniform_real_distribution<double> uni_dist(a, b);
		return uni_dist(engine_);
	};
private:
	std::random_device device_;
	std::default_random_engine engine_;
};

namespace Shape { enum { CIRCLE, SQUARE }; }

struct Particle
{
	vec2 pos; // Position
	vec2 vel; // Velocity
	vec4 color;  // RGBA
};

class ParticleSystem : public GameObject
{
public:
	ParticleSystem();

	void init(vec3 color);

	void setGravity(float x, float y) { m_gravity.x = x; m_gravity.y = y; }
	void setParticleSpeed(float speed) { m_particleSpeed = speed; }
	void setDissolve(bool enable) { m_dissolve = enable; }
	void setDissolutionRate(unsigned char rate) { m_dissolutionRate = rate; }
	void setShape(unsigned char shape) { m_shape = shape; }

	void setActive(bool active) { m_active = active; }

	virtual void doPhysicStep(); // Updates position, velocity and opacity of all particles

protected:
	virtual void render() const;

private:
	vec2			m_gravity;  // Affects particle velocities
	Randomizer		m_randomizer;
	float		    m_particleSpeed; // Pixels per second (at most)
	float			m_particleSize; // Size of a particle
	bool			m_dissolve; // Dissolution enabled?
	float			m_dissolutionRate; // percentage of alpha lost every frame
	unsigned char   m_shape;
	bool			m_active;

	static const int capacity = 100;
	Particle m_particles[capacity];
};
