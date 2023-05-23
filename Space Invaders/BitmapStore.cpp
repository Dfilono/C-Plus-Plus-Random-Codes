#include <assert.h>
#include <iostream>
#include "BitmapStore.h"


using namespace sf;
using namespace std;

BitmapStore* BitmapStore::m_s_Instance = nullptr;

BitmapStore::BitmapStore() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

void BitmapStore::addBitmap(std::string const& filename) {
	// Get reference to m_Textures using m_s_Instance
	auto& bitmapsMap = m_s_Instance->m_BitmapsMap;

	// Create iterator to hold kvp and search for required kvp
	auto keyValuePair = bitmapsMap.find(filename);

	if (keyValuePair == bitmapsMap.end()) {
		// Create new kvp
		auto& texture = bitmapsMap[filename];
		texture.loadFromFile(filename);
	}
}

sf::Texture& BitmapStore::getBitmap(std::string const& filename) {
	auto& m = m_s_Instance->m_BitmapsMap;
	auto keyValuePair = m.find(filename);

	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
#ifndef debuggingOnConsole
		cout << "BitmapStore::getBitmap() Texture not found. Crash!" << endl;
#endif // !debuggingOnConsole
		
		return keyValuePair->second;
	}
}