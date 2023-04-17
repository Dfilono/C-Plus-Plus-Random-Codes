#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	
	// Where is the player
	Vector2f m_Pos;

	// Player sprite
	Sprite m_Sprite;
	Texture m_Texture;

	// Screen Res
	Vector2f m_Res;

	// Arena size
	IntRect m_Arena;
	int m_TileSize;

	// Direction player is moving
	bool m_Up;
	bool m_Down;
	bool m_Left;
	bool m_Right;

	// Player health
	int m_Health;
	int m_MaxHealth;

	// Player last hit
	Time m_LastHit;

	// spped
	float m_Speed;

public:
	Player();

	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	void resetPlayerStats();

	bool hit(Time timeHit);

	Time getLastHit();

	FloatRect getPosition();

	Vector2f getCenter();

	float getRotation();

	Sprite getSprite();

	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	void stopLeft();

	void stopRight();

	void stopUp();

	void stopDown();

	void update(float elapsedTime, Vector2i mousePos);

	void upgradeSpeed();

	void upgradeHealth();

	void increaseHealthLevel(int amount);

	int getHealth();
};