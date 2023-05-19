#include "Engine.h"

void Engine::loadLevel() {
	m_Playing = false;

	// Delete previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i) {
		delete[] m_ArrayLevel[i];
	}

	delete[] m_ArrayLevel;

	// Load next 2d array with the map for level and repop VA
	m_ArrayLevel = m_LM.nextLevel(m_VaLevel);

	// Prepare sound emitters
	populateEmitters(m_FireEmitters, m_ArrayLevel);

	// Set up lvl
	m_TimeRemains = m_LM.getTimeLimit();
	m_Thomas.spawn(m_LM.getStartPos(), GRAVITY);
	m_Bob.spawn(m_LM.getStartPos(), GRAVITY);

	// Make sure this code isn't run again
	m_LoadNewLevel = false;
}