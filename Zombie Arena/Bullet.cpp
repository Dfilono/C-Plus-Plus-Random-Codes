#include "Bullet.h"

// constructor
Bullet::Bullet() {
	m_BulletShape.setSize(sf::Vector2f(2,2));
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY) {
	// Track bullet
	m_InFlight = true;
	m_Pos.x = startX;
	m_Pos.y = startY;

	// calculate flight path gradient
	float gradient = (startX - targetX) / (startY - targetY);
	if (gradient < 0) {
		gradient *= -1;
	}

	// calculate ration between x and y
	float ratioXY = m_BulletSpd / (1 + gradient);

	// set speed
	m_BulletDistanceY = ratioXY;
	m_BulletDistanceX = ratioXY * gradient;

	// point bullet in right direction
	if (targetX < startX) {
		m_BulletDistanceX *= -1;
	}

	if (targetY < startY) {
		m_BulletDistanceY *= -1;
	}

	// set max range
	float range = 1000;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;

	// set pos
	m_BulletShape.setPosition(m_Pos);
}

void Bullet::stop() {
	m_InFlight = false;
}

bool Bullet::isInFlight() {
	return m_InFlight;
}

FloatRect Bullet::getPos() {
	return m_BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape() {
	return m_BulletShape;
}

void Bullet::update(float elapsedTime) {
	// update bullet pos
	m_Pos.x += m_BulletDistanceX * elapsedTime;
	m_Pos.y += m_BulletDistanceY * elapsedTime;

	// move bullet
	m_BulletShape.setPosition(m_Pos);

	// in range?
	if (m_Pos.x < m_MinX || m_Pos.x > m_MaxX || m_Pos.y < m_MinY || m_Pos.y > m_MaxY) {
		m_InFlight = false;
	}
}