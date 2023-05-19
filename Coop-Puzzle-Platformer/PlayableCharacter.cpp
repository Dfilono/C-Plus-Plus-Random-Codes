#include "PlayableCharacter.h"

void PlayableCharacter::spawn(Vector2f startPos, float gravity) {
	// place player at start pos
	m_Pos.x = startPos.x;
	m_Pos.y = startPos.y;

	// init gravity
	m_Gravity = gravity;

	// move sprite in to position
	m_Sprite.setPosition(m_Pos);
}

void PlayableCharacter::update(float elapsedTime) {
	if (m_RightPressed) {
		m_Pos.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed) {
		m_Pos.x -= m_Speed * elapsedTime;
	}

	if (m_IsJump) {
		m_CurrentJumpTime += elapsedTime;

		if (m_CurrentJumpTime < m_JumpTime) {
			m_Pos.y -= m_Gravity * 2 * elapsedTime;
		}
		else {
			m_IsJump = false;
			m_IsFall = true;
		}
	}

	if (m_IsFall) {
		m_Pos.y += m_Gravity * elapsedTime;
	}

	FloatRect r = getPos();

	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;

	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * 0.3);
	m_Head.width = r.width;
	m_Head.height = 1;

	m_Right.left = r.left + r.width - 2;
	m_Right.top = r.top + r.height * 0.35;
	m_Right.width = 1;
	m_Right.height = r.height * 0.3;

	m_Left.left = r.left;
	m_Left.top = r.top + r.height * 0.5;
	m_Left.width = 1;
	m_Left.height = r.height * 0.3;

	m_Sprite.setPosition(m_Pos);
}

FloatRect PlayableCharacter::getPos() {
	return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::getCenter() {
	return Vector2f(
		m_Pos.x + m_Sprite.getGlobalBounds().width / 2,
		m_Pos.y + m_Sprite.getGlobalBounds().height / 2
	);
}

FloatRect PlayableCharacter::getFeet() {
	return m_Feet;
}

FloatRect PlayableCharacter::getHead() {
	return m_Head;
}

FloatRect PlayableCharacter::getLeft() {
	return m_Left;
}

FloatRect PlayableCharacter::getRight() {
	return m_Right;
}

Sprite PlayableCharacter::getSprite() {
	return m_Sprite;
}

void PlayableCharacter::stopFall(float pos) {
	m_Pos.y = pos - getPos().height;
	m_Sprite.setPosition(m_Pos);
	m_IsFall = false;
}

void PlayableCharacter::stopRight(float pos) {
	m_Pos.x = pos - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Pos);
}

void PlayableCharacter::stopLeft(float pos) {
	m_Pos.x = pos + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Pos);
}

void PlayableCharacter::stopJump() {
	m_IsJump = false;
	m_IsFall = true;
}