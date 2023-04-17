#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie {
private:
	// speed of each zombie type
	const float BLOATER_SPD = 40;
	const float CHASER_SPD = 80;
	const float CRAWLER_SPD = 20;

	// Health of each zombie type
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	// Slight variation in speed for each zombie
	const int MAX_VARY = 30;
	const int OFFSET = 101 - MAX_VARY;

	// Zombie position
	Vector2f m_Pos;

	// Zombie sprite
	Sprite m_Sprite;

	// attribtues
	float m_Speed;
	float m_Health;
	bool m_Alive;

public:
	// Is hit?
	bool hit();

	// Is alive?
	bool isAlive();

	// Spawn
	void spawn(float startX, float startY, int type, int seed);

	// Find Pos
	FloatRect getPos();

	// Find Sprite
	Sprite getSprite();

	// update frame
	void update(float elapsedTime, Vector2f playerLocation);

};