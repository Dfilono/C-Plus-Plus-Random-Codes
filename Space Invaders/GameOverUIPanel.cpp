#include "GameOverUIPanel.h"
#include "GameScreen.h"

bool GameScreen::m_GameOver;

GameOverUIPanel::GameOverUIPanel(Vector2i res) : UIPanel(res, (res.x / 10) * 3, res.y / 2, (res.x / 10) * 3, res.y / 6, 50, 255, 255, 255) {
	m_ButtonWidth = res.x / 20;
	m_ButtonHeight = res.y / 20;
	m_ButtonPAdding = res.x / 100;

	m_Text.setFillColor(sf::Color(0, 255, 0, 255));
	m_Text.setString("GAME OVER!");

	m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
	m_Text.setFont(m_Font);

	m_Text.setPosition(Vector2f(m_ButtonPAdding, (m_ButtonPAdding * 2) + m_ButtonHeight));
	m_Text.setCharacterSize(50);

	initButtons();
}

void GameOverUIPanel::initButtons() {
	addButton(m_ButtonPAdding, m_ButtonPAdding, m_ButtonWidth, m_ButtonHeight, 0, 255, 0, "Play");
	addButton(m_ButtonWidth + (m_ButtonPAdding * 2), m_ButtonPAdding, m_ButtonWidth, m_ButtonHeight, 255, 0, 0, "Home");
}

void GameOverUIPanel::draw(RenderWindow& window) {
	if (GameScreen::m_GameOver) {
		show();
		UIPanel::draw(window);
		window.draw(m_Text);
	}
	else {
		hide();
	}
}