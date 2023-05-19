#include "Engine.h"

Engine::Engine() {
	// Get screen res and create SFML window and View
	Vector2f res;
	res.x = VideoMode::getDesktopMode().width;
	res.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(res.x, res.y), "Thomas Was Late", Style::Fullscreen);

	// Init fullscreen view
	m_MainView.setSize(res);
	m_HudView.reset(FloatRect(0, 0, res.x, res.y));

	// Init split screen views
	m_LeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_BG_LeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	m_RightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
	m_BG_RightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	// check if GPU can use shaders
	if (!sf::Shader::isAvailable()) {
		// Time to get a new PC (or remove shaders code)
		m_Window.close();
	}
	else {
		// Load two shaders
		m_RippleShader.loadFromFile("shaders/vertShader.vert", "shaders/rippleShader.frag");
	}

	// Set background texture
	m_BG_Texture = TextureHolder::GetTexture("graphics/background.png");
	m_BG_Sprite.setTexture(m_BG_Texture);

	// Load Texture for background vertex array
	m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");

	// init particle system
	m_PS.init(1000);

}

void Engine::run() {
	// FPS control
	Clock clock;

	while (m_Window.isOpen()) {
		Time dt = clock.restart();
		m_GameTotalTime += dt;
		float dtAsSeconds = dt.asSeconds();

		// Call each part of game loop
		input();
		update(dtAsSeconds);
		draw();
	}
}