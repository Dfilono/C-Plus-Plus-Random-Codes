#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main() {
	// Create a video mode obj
	VideoMode vm(1920, 1080);

	// Create and open a window for game
	RenderWindow window(vm, "Pong", Style::Fullscreen);

	int score = 0;
	int lives = 3;

	// Create bat at bottom center of screen
	Bat bat(1920 / 2, 1080 - 20);

	// Create ball
	Ball ball(1920 / 2, 0);

	// Init HUD
	Text hud;
	Font font;
	font.loadFromFile("fonts/DS-DIGI.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	// FPS control
	Clock clock;

	// Game loop
	while (window.isOpen()) {
		// Player Input
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			bat.moveLeft();
		}
		else {
			bat.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			bat.moveRight();
		}
		else {
			bat.stopRight();
		}

		// Update bat, ball, HUD
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);
		std::stringstream ss;
		ss << "Score: " << score << "  Lives: " << lives;
		hud.setString(ss.str());

		// Ball hitting bottom
		if (ball.getPosition().top > window.getSize().y) {
			ball.reboundBottom();
			lives--;

			if (lives < 1) {
				score = 0;
				lives = 3;
				ball.setSpeed();
			}
		}

		// Ball hitting top
		if (ball.getPosition().top < 0) {
			ball.reboundBatOrTop();
			score++;
		}

		// Ball hitting sides
		if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x) {
			ball.reboundSides();
		}

		// Ball hitting bat
		if (ball.getPosition().intersects(bat.getPosition())) {
			ball.reboundBatOrTop();
		}


		// Draw
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}