#include "Engine.h"

using namespace sf;
using namespace std;

void Engine::populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel) {
	vSoundEmitters.empty();
	
	FloatRect previousEmitter;

	// search for fire in level
	for (int x = 0; x < (int)m_LM.getLevelSize().x; x++) {
		for (int y = 0; y < (int)m_LM.getLevelSize().y; y++) {
			if (arrayLevel[y][x] == 2) { // Fire is present
				// Skip any tiles too close to previous emitter
				if (!FloatRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE).intersects(previousEmitter)) {
					vSoundEmitters.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));

					// make a box so emitters wont be too close
					previousEmitter.left = x * TILE_SIZE;
					previousEmitter.top = y * TILE_SIZE;
					previousEmitter.width = TILE_SIZE * 6;
					previousEmitter.height = TILE_SIZE * 6;
				}
			}
		}
	}

	return;
}