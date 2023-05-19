#include "Engine.h"

void Engine::draw() {
	m_Window.clear(Color::White);

	// Update shader parameters
	m_RippleShader.setUniform("uTime", m_GameTotalTime.asSeconds());

	if (!m_SplitScreen) {
		// switch to background view
		m_Window.setView(m_BG_MainView);

		// draw background
		//m_Window.draw(m_BG_Sprite);

		// Draw bacgkround and shader
		m_Window.draw(m_BG_Sprite, &m_RippleShader);

		// switch to main view
		m_Window.setView(m_MainView);

		// Draw the level
		m_Window.draw(m_VaLevel, &m_TextureTiles);

		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());

		// Draw the particle system
		if (m_PS.running()) {
			m_Window.draw(m_PS);
		}
	}
	else {
		// Draw left side of screen
		// switch to background left view
		m_Window.setView(m_BG_LeftView);

		// Draw Background
		//m_Window.draw(m_BG_Sprite);

		// Draw bacgkround and shader
		m_Window.draw(m_BG_Sprite, &m_RippleShader);

		// Switch to Left view
		m_Window.setView(m_LeftView);

		// Draw the level
		m_Window.draw(m_VaLevel, &m_TextureTiles);

		m_Window.draw(m_Bob.getSprite());
		m_Window.draw(m_Thomas.getSprite());

		if (m_PS.running()) {
			m_Window.draw(m_PS);
		}

		// Draw right side of screen
		// switch to background right view
		m_Window.setView(m_BG_RightView);

		// Draw Background
		//m_Window.draw(m_BG_Sprite);

		// Draw bacgkround and shader
		m_Window.draw(m_BG_Sprite, &m_RippleShader);

		// Switch to right view
		m_Window.setView(m_RightView);

		// Draw the level
		m_Window.draw(m_VaLevel, &m_TextureTiles);

		m_Window.draw(m_Bob.getSprite());
		m_Window.draw(m_Thomas.getSprite());

		if (m_PS.running()) {
			m_Window.draw(m_PS);
		}
	}

	// Draw HUD
	// switch to Hud View
	m_Window.setView(m_HudView);
	m_Window.draw(m_Hud.getLevel());
	m_Window.draw(m_Hud.getTime());

	if (!m_Playing) {
		m_Window.draw(m_Hud.getMessage());
	}

	m_Window.display();
}