#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "GameScreen.h"
#include "ScreenManagerRemoteControl.h"
#include "SelectScreen.h"
// #include "LevelManager.h"
#include "BitmapStore.h"

using namespace sf;
using namespace std;

class ScreenManager : public ScreenManagerRemoteControl {
private:
	map <string, unique_ptr<Screen>> m_Screens;
	// LevelManager m_LevelManager;

protected:
	string m_CurrentScreen = "Select";

public:
	BitmapStore m_BS;

	ScreenManager(Vector2i res);
	void update(float fps);
	void draw(RenderWindow& window);
	void handleInput(RenderWindow& window);

	void ScreenManagerRemoteControl::SwitchScreens(string screenToSwitchTo) {
		m_CurrentScreen = "" + screenToSwitchTo;
		m_Screens[m_CurrentScreen]->initialise();
	}

	void ScreenManagerRemoteControl::loadLevelInPlayMode(string screenToLoad) {
		//m_LevelManager.getGameObjects().clear();
		//mm_LevelManager.loadGameObjectsForPlayMode(screenToLoad);
		SwitchScreens("Game");
	}

	//vector<GameObject>& ScreenManagerRemoteControl::getGameObjects() {
		//return m_LevelManager.getGameObjects();
	//}

	//GameObjectSharer& shareGameObjectSharer() {
		//return m_LevelManager; 
	//}
	
};