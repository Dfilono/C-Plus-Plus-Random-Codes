#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
private:
	// Bullet pos
	Vector2f m_Pos;

	// Bullt shape
	RectangleShape m_BulletShape;

	// Bullet shot
	bool m_InFlight = false;

	// bullet speed
	float m_BulletSpd = 1000;
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// bullet bounds
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

public:
	Bullet();

	//stop the bullet
	void stop();

	// is shot
	bool isInFlight();

	// shoot
	void shoot(float startX, float startY, float xTarget, float yTarget);

	// get bullet positions
	FloatRect getPos();

	// bullet shape
	RectangleShape getShape();

	// update bullet
	void update(float elapsedTime);
};