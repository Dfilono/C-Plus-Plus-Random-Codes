#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void Zombie::spawn(float startX, float startY, int type, int seed) {
	switch (type) {
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
		m_Speed = BLOATER_SPD;
		m_Health = BLOATER_HEALTH;
		break;
	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
		m_Speed = CHASER_SPD;
		m_Health = CHASER_HEALTH;
		break;
	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
		m_Speed = CRAWLER_SPD;
		m_Health = CRAWLER_HEALTH;
		break;
	}

	// Modify speed for each zombie
	srand((int)time(0) * seed);
	float modifier = (rand() % MAX_VARY) + OFFSET;
	modifier /= 100;
	m_Speed *= modifier;

	// Init start location
	m_Pos.x = startX;
	m_Pos.y = startY;
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Pos);
}

bool Zombie::hit() {
	m_Health--;

	if (m_Health <= 0) {
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));

		return true;
	}

	// injured, but noy dead
	return false;
}

bool Zombie::isAlive() {
	return m_Alive;
}

FloatRect Zombie::getPos() {
	return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite() {
	return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// update zombie positions
	if (playerX > m_Pos.x) {
		m_Pos.x = m_Pos.x + m_Speed * elapsedTime;
	}

	if (playerY > m_Pos.y) {
		m_Pos.y = m_Pos.y + m_Speed * elapsedTime;
	}

	if (playerX < m_Pos.x) {
		m_Pos.x = m_Pos.x - m_Speed * elapsedTime;
	}

	if (playerY < m_Pos.y) {
		m_Pos.y = m_Pos.y - m_Speed * elapsedTime;
	}

	// Move Sprite
	m_Sprite.setPosition(m_Pos);

	// Face sprite in correct direction
	float angle = (atan2(playerY - m_Pos.y, playerX - m_Pos.x) * 180) / 3.141;
	m_Sprite.setRotation(angle);
}