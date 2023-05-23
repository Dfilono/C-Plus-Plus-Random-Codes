#include <sstream>
#include<iostream>
#include "InputHandler.h"

using namespace sf;
using namespace std;

void InputHandler::initInputHandler(ScreenManagerRemoteControl* sw, vector<shared_ptr<Button>> buttons, View* pointerToUIView, Screen* parentScreen) {
	m_ScreenManagerRemoteControl = sw;
	m_Buttons = buttons;
	m_PointerToUIPanelView = pointerToUIView;
	m_ParentScreen = parentScreen;
}

void InputHandler::handleInput(RenderWindow& window, Event& event) {
	// Handle any key presses
	if (event.type == Event::KeyPressed) {
		handleKeyPressed(event, window);
	}

	if (event.type == Event::KeyReleased) {
		handleKeyReleased(event, window);
	}

	// Handle any left mouse click released
	if (event.type == Event::MouseButtonReleased) {
		auto end = m_Buttons.end();

		for (auto i = m_Buttons.begin(); i != end; ++i) {
			if ((*i)->m_Collider.contains(window.mapPixelToCoords(Mouse::getPosition(), (*getPointToUIView())))) {
				handleLeftClick((*i)->m_Text, window);
				break;
			}
		}
	}

	handleGamepad();
}

void InputHandler::handleGamepad(){} // Do nothing unless handled by a derived class
void InputHandler::handleKeyPressed(Event& event, RenderWindow& window){} // Do nothing unless handled by a derived class
void InputHandler::handleKeyReleased(Event& event, RenderWindow& window){} // Do nothing unless handled by a derived class
void InputHandler::handleLeftClick(std::string& buttonInteractedWith, RenderWindow& window){} // Do nothing unless handled by a derived class

View* InputHandler::getPointToUIView() {
	return m_PointerToUIPanelView;
}

ScreenManagerRemoteControl* InputHandler::getPointerToScreenManagerRemoteControl() {
	return m_ScreenManagerRemoteControl;
}

Screen* InputHandler::getmParentsScreen() {
	return m_ParentScreen;
}
