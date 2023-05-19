#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob() {
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bob.png"));
	m_JumpTime = 0.25;
}

bool Bob::handleInput() {
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (!m_IsJump && !m_IsFall) {
			m_IsJump = true;
			m_CurrentJumpTime = 0;
			m_JustJumped = true;
		}
	}
	else {
		m_IsJump = false;
		m_IsFall = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		m_RightPressed = true;
	}
	else {
		m_RightPressed = false;
	}

	return m_JustJumped;
}