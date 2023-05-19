#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds) {
	if (m_LoadNewLevel) {
		m_Thomas.spawn(Vector2f(0, 0), GRAVITY);
		m_Bob.spawn(Vector2f(100, 0), GRAVITY);

		m_TimeRemains = 10;
		m_LoadNewLevel = false;

		loadLevel();
	}

	if (m_Playing) {
		m_Thomas.update(dtAsSeconds);
		m_Bob.update(dtAsSeconds);

		// Detect collisions and see if goal has been reached
		if (detectCollisions(m_Thomas) && detectCollisions(m_Bob)) {
			// New lvl required
			m_LoadNewLevel = true;

			// Play win sound
			m_SM.playReachGoal();
		}
		else {
			detectCollisions(m_Bob);
		}

		// Let characters jump on each others heads
		if (m_Bob.getFeet().intersects(m_Thomas.getHead())) {
			m_Bob.stopFall(m_Thomas.getHead().top);
		}
		else if (m_Thomas.getFeet().intersects(m_Bob.getHead())) {
			m_Thomas.stopFall(m_Bob.getHead().top);
		}

		// Count down time player has left
		m_TimeRemains -= dtAsSeconds;

		if (m_TimeRemains <= 0) {
			m_LoadNewLevel = true;
		}
	}

	// check if fire sound needs to be played
	vector<Vector2f>::iterator it;
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++) {
		// Where is the emitter
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emitter near the playeR?
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// is player inside local rect
		if (m_Thomas.getPos().intersects(localRect)) {
			// play fire sound and pass in location
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}

	if (m_SplitScreen) {
		m_LeftView.setCenter(m_Thomas.getCenter());
		m_RightView.setCenter(m_Bob.getCenter());
	}
	else {
		if (m_Char1) {
			m_MainView.setCenter(m_Thomas.getCenter());
		}
		else {
			m_MainView.setCenter(m_Bob.getCenter());
		}
	}

	// Time to update the HUD
	m_FramesSinceLastHUDUpdate++;

	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate) {
		// update game hud
		stringstream ssTime;
		stringstream ssLevel;

		// Update time text
		ssTime << (int)m_TimeRemains;
		m_Hud.setTime(ssTime.str());

		// Update level text
		ssLevel << "Level: " << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update particles
	if (m_PS.running()) {
		m_PS.update(dtAsSeconds);
	}
}