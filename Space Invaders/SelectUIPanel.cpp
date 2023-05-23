#include <iostream>
#include "SelectUIPanel.h"

SelectUIPanel::SelectUIPanel(Vector2i res) : UIPanel(res, res.x / 10, res.y / 3, (res.x / 10) * 6, res.y / 3, 50, 255, 255, 255) {
	m_ButtonWidth = res.x / 20;
	m_ButtonHeight = res.y / 20;
	m_ButtonPAdding = res.x / 100;

	m_Text.setFillColor(sf::Color(0, 255, 0, 255));
	m_Text.setString("SPACE INVADERS ++");

	m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
	m_Text.setFont(m_Font);

	m_Text.setPosition(Vector2f(m_ButtonPAdding, m_ButtonHeight + (m_ButtonPAdding * 2)));
	m_Text.setCharacterSize(120);

	initButtons();
}

void SelectUIPanel::initButtons() {
	addButton(m_ButtonPAdding, m_ButtonPAdding, m_ButtonWidth, m_ButtonHeight, 0, 255, 0, "Play");
	addButton(m_ButtonWidth + (m_ButtonPAdding * 2), m_ButtonPAdding, m_ButtonWidth, m_ButtonHeight, 255, 0, 0, "Quit");
}

void SelectUIPanel::draw(RenderWindow& window) {
	show();
	UIPanel::draw(window);
	window.draw(m_Text);
}

