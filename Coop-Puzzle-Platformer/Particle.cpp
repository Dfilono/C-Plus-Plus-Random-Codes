#include "Particle.h"

Particle::Particle(Vector2f direction) {
	// DEtermine the direction
	m_Vel.x = direction.x;
	m_Vel.y = direction.y;
}

void Particle::update(float dt) {
	// move particle
	m_Pos += m_Vel * dt;
}

void Particle::setPosition(Vector2f position) {
	m_Pos = position;
}

Vector2f Particle::getPos() {
	return m_Pos;
}