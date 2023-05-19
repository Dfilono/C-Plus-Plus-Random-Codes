#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Particle {
private:
	Vector2f m_Pos;
	Vector2f m_Vel;

public:
	Particle(Vector2f direction);
	void update(float dt);
	void setPosition(Vector2f position);
	Vector2f getPos();
};