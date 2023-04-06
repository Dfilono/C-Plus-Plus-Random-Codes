#include <SDL.h>
#include <vector>
#include <algorithm>
#include <deque>
#undef main

// Global Vars
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

int main() {

	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	auto renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;

	enum direction{DOWN, LEFT, RIGHT, UP};
	bool running = true;
	int dir = 0;
	SDL_Rect head{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 10, 10};

	// Snake Body
	std::deque<SDL_Rect> rq;
	int size = 1;

	// Food
	std::vector<SDL_Rect> food;
	food.emplace_back(rand() % 100 * 10, rand() % 100 * 10, 10, 10);

	while (running) {
		// Check Input
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s) {
					dir = DOWN;
				}
				if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w) {
					dir = UP;
				}
				if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a) {
					dir = LEFT;
				}
				if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d) {
					dir = RIGHT;
				}
				
			}
		}
		
		// Move
		switch (dir) {
		case DOWN:
			head.y += 10;
			break;

		case UP:
			head.y -= 10;
			break;

		case LEFT:
			head.x -= 10;
			break;

		case RIGHT:
			head.x += 10;
			break;
		}

		// Collision with food
		std::for_each(food.begin(), food.end(), [&](auto& e) {
			if (head.x == e.x && head.y == e.y) {
				size += 1;
				e.x = -10;
				e.y = 10;
				food.emplace_back(rand() % 100 * 10, rand() % 100 * 10, 10, 10);
			}
		});

		// Collision with body
		std::for_each(rq.begin(), rq.end(), [&](auto& seg) {
			if (head.x == seg.x && head.y == seg.y) {
				size = 1;
				head.x = WINDOW_WIDTH / 2;
				head.y = WINDOW_HEIGHT / 2;
			}
		});

		// Collision walls
		if (head.x < 0 || head.x > WINDOW_WIDTH || head.y < 0 || head.y > WINDOW_HEIGHT) {
			size = 1;
			head.x = WINDOW_WIDTH / 2;
			head.y = WINDOW_HEIGHT / 2;
		}

		rq.push_front(head);

		while (rq.size() > size) {
			rq.pop_back();
		}

		

		// Clear Window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw Body
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		std::for_each(rq.begin(), rq.end(), [&](auto& seg) {
			SDL_RenderFillRect(renderer, &seg);
		});

		// Draw Food
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		std::for_each(food.begin(), food.end(), [&](auto& e) {
			SDL_RenderFillRect(renderer, &e);
		});

		// Display
		SDL_RenderPresent(renderer);
		SDL_Delay(25);
	}

	return 0;
}