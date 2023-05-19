#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

// Constructor
TextureHolder::TextureHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename) {
	// Get a reference to m_Textures using the m_s_Instance
	auto& m = m_s_Instance->m_Textures;
	
	// Create iterator that holds a key-value pair and search for required pair
	auto KVP = m.find(filename);

	if (KVP != m.end()) {
		// Value found
		return KVP->second;
	}
	else {
		// Not found
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}
