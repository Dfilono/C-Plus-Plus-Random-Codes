#include "Thomas.h"
#include "TextureHolder.h"

Thomas::Thomas() {
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/thomas.png"));
	m_JumpTime = 0.45;
}

bool Thomas::handleInput() {
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::W)) {
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

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		m_RightPressed = true;
	}
	else {
		m_RightPressed = false;
	}

	return m_JustJumped;
}