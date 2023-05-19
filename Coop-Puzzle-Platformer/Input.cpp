#include "Engine.h"

void Engine::input() {
	Event event;

	while (m_Window.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {
			// handle player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				m_Window.close();
			}

			// starting the game
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				m_Playing = true;
			}

			// switch characters
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				m_Char1 = !m_Char1;
			}

			// switch from fullscreen and splitscreen
			if (Keyboard::isKeyPressed(Keyboard::E)) {
				m_SplitScreen = !m_SplitScreen;
			}
		}
	}

	if (m_Thomas.handleInput()) {
		// play jump sound
		m_SM.playJump();
	}

	if (m_Bob.handleInput()) {
		// play jump sound
		m_SM.playJump();
	}
}