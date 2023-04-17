#include "Player.h"
#include "TextureHolder.h"

Player::Player() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/player.png"));

	m_Sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize) {
	// Place player in middle of arena
	m_Pos.x = arena.width / 2;
	m_Pos.y = arena.height / 2;

	// Copy details of the arean to player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;
	m_TileSize = tileSize;

	// Store resolution
	m_Res.x = resolution.x;
	m_Res.y = resolution.y;
}

void Player::resetPlayerStats() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

Time Player::getLastHit() {
	return m_LastHit;
}

bool Player::hit(Time timeHit) {
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) {
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else {
		return false;
	}
}

FloatRect Player::getPosition() {
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter() {
	return m_Pos;
}

float Player::getRotation() {
	return m_Sprite.getRotation();
}

Sprite Player::getSprite() {
	return m_Sprite;
}

int Player::getHealth() {
	return m_Health;
}

void Player::moveLeft() {
	m_Left = true;
}

void Player::moveRight() {
	m_Right = true;
}

void Player::moveUp() {
	m_Up = true;
}

void Player::moveDown() {
	m_Down = true;
}

void Player::stopLeft() {
	m_Left = false;
}

void Player::stopRight() {
	m_Right = false;
}

void Player::stopDown() {
	m_Down = false;
}

void Player::stopUp() {
	m_Up = false;
}

void Player::update(float elaspedTime, Vector2i mousePos) {
	if (m_Up) {
		m_Pos.y -= m_Speed * elaspedTime;
	}

	if (m_Down) {
		m_Pos.y += m_Speed * elaspedTime;
	}

	if (m_Right) {
		m_Pos.x += m_Speed * elaspedTime;
	}

	if (m_Left) {
		m_Pos.x -= m_Speed * elaspedTime;
	}

	m_Sprite.setPosition(m_Pos);

	// Keep player in arena
	if (m_Pos.x > m_Arena.width - m_TileSize) {
		m_Pos.x = m_Arena.width - m_TileSize;
	}

	if (m_Pos.x < m_Arena.left + m_TileSize) {
		m_Pos.x = m_Arena.left + m_TileSize;
	}

	if (m_Pos.y > m_Arena.height - m_TileSize) {
		m_Pos.y = m_Arena.height - m_TileSize;
	}

	if (m_Pos.y < m_Arena.top + m_TileSize) {
		m_Pos.y = m_Arena.top + m_TileSize;
	}

	// Calculate angle player is facing
	float angle = (atan2(mousePos.y - m_Res.y / 2, mousePos.x - m_Res.x / 2) * 180) / 3.141;
	m_Sprite.setRotation(angle);
}

void Player::upgradeSpeed() {
	m_Speed += (START_SPEED * 0.2);
}

void Player::upgradeHealth() {
	m_MaxHealth += (START_HEALTH * 0.2);
}

void Player::increaseHealthLevel(int amount) {
	m_Health += amount;

	if (m_Health > m_MaxHealth) {
		m_Health = m_MaxHealth;
	}
}