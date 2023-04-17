#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup {
private:
	// Start value for pickups
	const int HEALTH_START_VAL = 50;
	const int AMMO_START_VAL = 12;
	const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;

	// sprite for pickup
	Sprite m_Sprite;

	// arena
	IntRect m_Arena;

	// pickup value
	int m_Val;

	// pickup type
	int m_Type;

	// spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDespawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

public:

	Pickup(int type);

	// prepare new pickup
	void setArena(IntRect arena);

	void spawn();

	// Check position
	FloatRect getPos();

	// get sprite
	Sprite getSprite();

	// update pikcup
	void update(float elapsedTime);

	// is spawned
	bool isSpawned();

	// picked up
	int gotIt();

	// upgrade value
	void upgrade();
};