#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter {
protected:
	Sprite m_Sprite;

	// how long does a jump last
	float m_JumpTime;

	// Is the character jumping or falling
	bool m_IsJump;
	bool m_IsFall;

	// Direction of movement
	bool m_LeftPressed;
	bool m_RightPressed;

	// How long left in current jump
	float m_CurrentJumpTime;

	// did the player just jump
	bool m_JustJumped = false;

private:
	float m_Gravity;
	float m_Speed = 400;
	Vector2f m_Pos;

	// Character body parts
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	Texture m_Texture;

public:
	void spawn(Vector2f startPos, float gravity);

	bool virtual handleInput() = 0;

	FloatRect getPos();
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	Sprite getSprite();

	void stopFall(float pos);
	void stopRight(float pos);
	void stopLeft(float pos);
	void stopJump();

	Vector2f getCenter();

	void update(float elpasedTime);
};
