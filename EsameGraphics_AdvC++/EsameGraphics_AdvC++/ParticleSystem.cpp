#include "ParticleSystem.h"
#include "SystemManager.h"
#include "glew.h"

ParticleSystem::ParticleSystem()
{
	m_particleSpeed = 2.0f;
	m_particleSize = 5.0f;
	m_dissolve = true;
	m_dissolutionRate = 0.005f;
	m_shape = Shape::CIRCLE;
	m_active = false;
}

void ParticleSystem::init(vec3 color)
{
	for (int i = 0; i < capacity; i++)
	{
		m_particles[i].pos.x = getPos().x;
		m_particles[i].pos.y = getPos().y;

		float angle;
		switch (m_shape)
		{
		case Shape::CIRCLE:
			angle = m_randomizer.rnd(0.0f, 6.2832f);
			m_particles[i].vel.x = cos(angle);
			m_particles[i].vel.y = sin(angle);
			break;
		case Shape::SQUARE:
			m_particles[i].vel.x = m_randomizer.rnd(-1.0f, 1.0f);
			m_particles[i].vel.y = m_randomizer.rnd(-1.0f, 1.0f);
			break;
		default:
			m_particles[i].vel.x = 0.5f; // Easily detected
			m_particles[i].vel.y = 0.5f; // Easily detected
		}
		float opacity = m_randomizer.rnd(0.0f, 1.0f);
		m_particles[i].color.r = opacity * color.r;
		m_particles[i].color.g = opacity * color.g;
		m_particles[i].color.b = opacity * color.b;
		m_particles[i].color.a = 1;
	}
}

void ParticleSystem::doPhysicStep()
{
	if (m_active)
	{
		float time = SystemManager::dt;

		for (int i = 0; i < capacity; i++)
		{
			m_particles[i].vel.x += m_gravity.x * time;
			m_particles[i].vel.y += m_gravity.y * time;

			m_particles[i].pos.x += m_particles[i].vel.x * time * m_particleSpeed;
			m_particles[i].pos.y += m_particles[i].vel.y * time * m_particleSpeed;

			if (m_dissolve) m_particles[i].color.a -= m_dissolutionRate;

			if (m_particles[i].color.a < 0.05)
			{
				m_active = false;
				break;
			}
		}
	}
}

void ParticleSystem::render() const
{
	if (m_active)
	{
		glPointSize(m_particleSize);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_POINTS);
		for (int i = 0; i < capacity; i++)
		{
			glColor4f(m_particles[i].color.r, m_particles[i].color.g, m_particles[i].color.b, m_particles[i].color.a);
			glVertex2f(m_particles[i].pos.x, m_particles[i].pos.y);
		}
		glEnd();
		glFlush();
		glDisable(GL_BLEND);
	}
}
