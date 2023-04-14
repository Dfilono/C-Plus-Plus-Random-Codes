#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
private:
	Vector2f m_Pos;
	RectangleShape m_Shape;

	float m_Speed = 300.0f;
	float m_DirectX = 0.2f;
	float m_DirectY = 0.2f;

public:
	Ball(float startX, float startY);

	FloatRect getPosition();

	RectangleShape getShape();

	float getXVel();

	void reboundSides();

	void reboundBatOrTop();

	void reboundBottom();

	void setSpeed();

	void update(Time dt);
};