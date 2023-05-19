#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"

using namespace sf;

class Engine {
private:
	TextureHolder th;

	ParticleSystem m_PS;

	Thomas m_Thomas;
	Bob m_Bob;

	LevelManager m_LM;

	SoundManager m_SM;

	// The Hud
	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	// Constatns
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;
	const int GRAVITY = 300;

	// Create Window
	RenderWindow m_Window;

	// Viewpoints
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	// Background views
	View m_BG_MainView;
	View m_BG_LeftView;
	View m_BG_RightView;

	View m_HudView;

	// Background sprite/texture
	Sprite m_BG_Sprite;
	Texture m_BG_Texture;

	// Declare a shader for BG
	Shader m_RippleShader;

	// is the game running?
	bool m_Playing = false;

	// Is character 1 or 2 the focus?
	bool m_Char1 = false;

	// Is the game in split screen?
	bool m_SplitScreen = false;

	// Time left is current level (seconds)
	float m_TimeRemains = 10;
	Time m_GameTotalTime;

	// Load a new level?
	bool m_LoadNewLevel = true;

	// Vertex Array for Level Tiles
	VertexArray m_VaLevel;

	// 2d array with map of level (pointer to a pointer)
	int** m_ArrayLevel = NULL;

	// Texture for level tiles
	Texture m_TextureTiles;

	void input();
	void update(float dtAsSeconds);
	void draw();
	void loadLevel();

	bool detectCollisions(PlayableCharacter& character);

	// Make a vector of the best places to emit sounds
	void populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel);
	vector <Vector2f> m_FireEmitters;

public:
	Engine();
	void run();
};