#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

using namespace sf;
using namespace std;

void ParticleSystem::init(int count) {
	m_Vertices.setPrimitiveType(Points);
	m_Vertices.resize(count);

	// Create particles
	for (int i = 0; i < count; i++) {
		srand(time(0) + i);
		float angle = (rand() % 360) * 3.14f / 180.f;
		float speed = (rand() % 600) + 600.0f;

		Vector2f direction;
		direction = Vector2f(cos(angle) * speed, sin(angle) * speed);

		m_Particles.push_back(Particle(direction));
	}
}

void ParticleSystem::update(float dt) {
	m_Duration -= dt;
	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++) {
		// move particle
		(*i).update(dt);

		// update vertex array
		m_Vertices[currentVertex++].position = i->getPos();
	}

	if (m_Duration < 0) {
		m_IsRunning = false;
	}
}

void ParticleSystem::emitParticles(Vector2f startPos) {
	m_IsRunning = true;
	m_Duration = 2;

	int currentVertex = 0;

	for (auto it = m_Particles.begin(); it != m_Particles.end(); it++) {
		m_Vertices[currentVertex++].color = Color::Yellow;
		it->setPosition(startPos);
	}
}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_Vertices, states);
}

bool ParticleSystem::running() {
	return m_IsRunning;
}