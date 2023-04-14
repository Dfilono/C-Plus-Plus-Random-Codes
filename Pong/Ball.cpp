#include "Ball.h"

// Constructor
Ball::Ball(float startX, float startY) {
	m_Pos.x = startX;
	m_Pos.y = startY;

	m_Shape.setSize(sf::Vector2f(10, 10));
	m_Shape.setPosition(m_Pos);
}

FloatRect Ball::getPosition() {
	return m_Shape.getGlobalBounds();
}

RectangleShape Ball::getShape() {
	return m_Shape;
}

float Ball::getXVel() {
	return m_DirectX;
}

void Ball::reboundSides() {
	m_DirectX = -m_DirectX;
}

void Ball::reboundBatOrTop() {
	m_DirectY = -m_DirectY;
	m_Speed = m_Speed * 1.1f;
}

void Ball::reboundBottom() {
	m_Pos.y = 0;
	m_Pos.x = 500;
	m_DirectY = m_DirectY;
}

void Ball::update(Time dt) {
	m_Pos.y += m_DirectY * m_Speed * dt.asSeconds();
	m_Pos.x += m_DirectX * m_Speed * dt.asSeconds();

	m_Shape.setPosition(m_Pos);
}

void Ball::setSpeed() {
	m_Speed = 300.0f;
}