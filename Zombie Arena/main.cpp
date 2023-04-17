#include <sstream>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "main.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"

using namespace sf;

int main() {
	// Instance of TextureHolder
	TextureHolder holder;

	// Four game states
	enum class State{PAUSED, LEVELING_UP, GAME_OVER, PLAYING};
	State state = State::GAME_OVER;

	// Get screen resolution and create window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

	// Create SFML view for main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// FPS control
	Clock clock;

	// How long has the playing state been active
	Time gameTimeTotal;

	// Relative mouse coords
	Vector2f mouseWorldPos;
	Vector2i mouseScreenPos;

	// Crate Player obj
	Player player;

	// Arena Boundries
	IntRect arena;

	// Create Background
	VertexArray background;
	Texture textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

	// Prepare zombies
	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = nullptr;

	// Prepare initial bullets
	Bullet bullets[100];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletInClip = 6;
	int clipSize = 6;
	float fireRate = 1;
	Time lastPressed;

	// turn mouse cursor into crosshair
	window.setMouseCursorVisible(false);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	// create pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	// Score
	int score = 0;
	int hiScore = 0;

	// HUD
	// game over screen
	Sprite spriteGameOver;
	Texture textureGameOver = TextureHolder::GetTexture("graphics/background.png");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	// HUD view
	View hudView(FloatRect(0, 0, resolution.x, resolution.y));

	// Ammo icon sprite
	Sprite spriteAmmoIcon;
	Texture textureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	// Load font
	Font font;
	font.loadFromFile("fonts/zombiecontrol.ttf");

	// Pause screen
	Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(400, 400);
	pausedText.setString("Press Enter \nto Continue");

	// Game Over txt
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(250, 850);
	gameOverText.setString("Press Enter to Play");

	// Leveling Up
	Text levelUpText;
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(80);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"1 - Increased rate of fire" <<
		"\n2 - Increased clip size (next reload)" <<
		"\n3 - Increased max health" <<
		"\n4 - Increased run speed" <<
		"\n5 - More and better health pickups" <<
		"\n6 - More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());

	// Ammo
	Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(200, 980);

	// Score
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 0);

	// Load high score from file
	std::ifstream inputFile("gamedata/scores.txt");

	if (inputFile.is_open()) {
		inputFile >> hiScore;
		inputFile.close();
	}

	// Hi-Score
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(1400, 0);
	std::stringstream s;
	s << "High Score: " << hiScore;
	hiScoreText.setString(s.str());

	// Zombies remaining
	Text zombiesRemainText;
	zombiesRemainText.setFont(font);
	zombiesRemainText.setCharacterSize(55);
	zombiesRemainText.setFillColor(Color::White);
	zombiesRemainText.setPosition(1500, 980);
	zombiesRemainText.setString("Zombies: 100");

	// Wave number
	int wave = 0;
	Text waveNumText;
	waveNumText.setFont(font);
	waveNumText.setCharacterSize(55);
	waveNumText.setFillColor(Color::White);
	waveNumText.setPosition(1250, 980);
	waveNumText.setString("Wave: 0");

	// Health bar
	RectangleShape healthBar;
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(450, 980);

	// When was the hud last updated?
	int framesSinceLastHUDUpdate = 0;

	// How often shoul the hud be updated?
	int fpsFrameInterval = 1000;

	// Audio
	// hi sound
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	Sound hit;
	hit.setBuffer(hitBuffer);

	// splat sound
	SoundBuffer splatBuffer;
	splatBuffer.loadFromFile("sound/splat.wav");
	Sound splat;
	splat.setBuffer(splatBuffer);

	// shoot sound
	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sound/shoot.wav");
	Sound shoot;
	shoot.setBuffer(shootBuffer);

	// reload sound
	SoundBuffer reloadBuffer;
	reloadBuffer.loadFromFile("sound/reload.wav");
	Sound reload;
	reload.setBuffer(reloadBuffer);

	// failed sound
	SoundBuffer reloadFailedBuffer;
	reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
	Sound reloadFailed;
	reloadFailed.setBuffer(reloadFailedBuffer);

	// powerup sound
	SoundBuffer powerupBuffer;
	powerupBuffer.loadFromFile("sound/powerup.wav");
	Sound powerup;
	powerup.setBuffer(powerupBuffer);

	// pickup sound
	SoundBuffer pickupBuffer;
	pickupBuffer.loadFromFile("sound/pickup.wav");
	Sound pickup;
	pickup.setBuffer(pickupBuffer);


	// Game loop
	while (window.isOpen()) {
		// Handle Events
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Return && state == State::PLAYING) {
					state = State::PAUSED;
				}
				else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
					state = State::PLAYING;
					clock.restart();
				}
				else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
					state = State::LEVELING_UP;
					wave = 0;
					score = 0;

					// Prepare gun and ammo
					currentBullet = 0;
					bulletInClip = 6;
					bulletsSpare = 24;
					clipSize = 6;
					fireRate = 1;

					// reset stats
					player.resetPlayerStats();
				}

				if (state == State::PLAYING) {
					if (event.key.code == Keyboard::R) {
						if (bulletsSpare >= clipSize) {
							// Reload
							bulletInClip = clipSize;
							bulletsSpare -= clipSize;
							reload.play();
						}
						else if (bulletsSpare > 0) {
							bulletInClip = bulletsSpare;
							bulletsSpare = 0;
							reload.play();
						}
						else {
							reloadFailed.play();
						}
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		// Handle WASD
		if (state == State::PLAYING) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				player.moveUp();
			}
			else {
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				player.moveDown();
			}
			else {
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player.moveLeft();
			}
			else {
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D)) {
				player.moveRight();
			}
			else {
				player.stopRight();
			}

			// Fire a bullet
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletInClip > 0) {
					bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPos.x, mouseWorldPos.y);
					currentBullet++;
					

					if (currentBullet > 99) {
						currentBullet = 0;
					}

					lastPressed = gameTimeTotal;
					shoot.play();
					bulletInClip--;
				}
			}
		}

		

		if (state == State::LEVELING_UP) {
			if (event.key.code == Keyboard::Num1) {
				fireRate++;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2) {
				clipSize += clipSize;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3) {
				player.upgradeHealth();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num4) {
				player.upgradeSpeed();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num5) {
				healthPickup.upgrade();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num6) {
				ammoPickup.upgrade();
				state = State::PLAYING;
			}

			if (state == State::PLAYING) {
				// Increase wave
				wave++;

				// Prepare level
				arena.width = 500 * wave;
				arena.height = 500 * wave;
				arena.left = 0;
				arena.top = 0;

				int tileSize = createBackground(background, arena);

				// Spawn player
				player.spawn(arena, resolution, tileSize);

				// Configure pickups
				healthPickup.setArena(arena);
				ammoPickup.setArena(arena);

				// Create horde of zombies
				numZombies = 5 * wave;
				delete[] zombies;
				zombies = createHorde(numZombies, arena);
				numZombiesAlive = numZombies;

				powerup.play();

				// set clock
				clock.restart();
			}
		}

		// Update the frame
		if (state == State::PLAYING) {
			Time dt = clock.restart();
			gameTimeTotal += dt;
			float dtAsSeconds = dt.asSeconds();

			// Mouse pointer
			mouseScreenPos = Mouse::getPosition();
			mouseWorldPos = window.mapPixelToCoords(Mouse::getPosition(), mainView);

			// Set crosshair
			spriteCrosshair.setPosition(mouseWorldPos);

			// Update player
			player.update(dtAsSeconds, Mouse::getPosition());
			Vector2f playerPos(player.getCenter());

			// Center view around the player
			mainView.setCenter(player.getCenter());

			// Update each zombie in array
			for (int i = 0; i < numZombies; i++) {
				if (zombies[i].isAlive()) {
					zombies[i].update(dt.asSeconds(), playerPos);
				}
			}

			// update bullets
			for (int i = 0; i < 100; i++) {
				if (bullets[i].isInFlight()) {
					bullets[i].update(dtAsSeconds);
				}
			}

			// update pickups
			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);

			//  Collisons
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < numZombies; j++) {
					if (bullets[i].isInFlight() && zombies[j].isAlive()) {
						if (bullets[i].getPos().intersects(zombies[j].getPos())) {
							bullets[i].stop();

							if (zombies[j].hit()) {
								score += 10;
								
								if (score >= hiScore) {
									hiScore = score;
								}

								numZombiesAlive--;
								
								if (numZombiesAlive == 0) {
									state = State::LEVELING_UP;
								}

								splat.play();
							}
						}
					}

				}
			}

			for (int i = 0; i < numZombies; i++) {
				if (player.getPosition().intersects(zombies[i].getPos()) && zombies[i].isAlive()) {
					if (player.hit(gameTimeTotal)) {
						hit.play();
					}

					if (player.getHealth() <= 0) {
						state = State::GAME_OVER;

						std::ofstream outputFile("gamedata/scores.txt");
						outputFile << hiScore;
						outputFile.close();
					}
				}
			}

			if (player.getPosition().intersects(healthPickup.getPos()) && healthPickup.isSpawned()) {
				player.increaseHealthLevel(healthPickup.gotIt());
				pickup.play();
			}

			if (player.getPosition().intersects(ammoPickup.getPos()) && ammoPickup.isSpawned()) {
				bulletsSpare += ammoPickup.gotIt();
				reload.play();
			}

			// size health bar
			healthBar.setSize(Vector2f(player.getHealth() * 3, 50));

			// Increment frames since last update
			framesSinceLastHUDUpdate++;
			
			if (framesSinceLastHUDUpdate > fpsFrameInterval) {
				// Update HUD text
				std::stringstream ssAmmo;
				std::stringstream ssScore;
				std::stringstream ssHiScore;
				std::stringstream ssWave;
				std::stringstream ssZombiesAlive;

				// update ammo txt
				ssAmmo << bulletInClip << "/" << bulletsSpare;
				ammoText.setString(ssAmmo.str());

				// update score txt
				ssScore << "Score: " << score;
				scoreText.setString(ssScore.str());

				// update the high score
				ssHiScore << "High Score: " << hiScore;
				hiScoreText.setString(ssHiScore.str());

				// update wave txt
				ssWave << "Wave: " << wave;
				waveNumText.setString(ssWave.str());

				// update zombies alive txt
				ssZombiesAlive << "Zombies: " << numZombiesAlive;
				zombiesRemainText.setString(ssZombiesAlive.str());

				framesSinceLastHUDUpdate = 0;
			}

		}

		// Draw
		if (state == State::PLAYING) {
			window.clear();
			window.setView(mainView);
			window.draw(background, &textureBackground);

			for (int i = 0; i < numZombies; i++) {
				window.draw(zombies[i].getSprite());
			}

			for (int i = 0; i < 100; i++) {
				if (bullets[i].isInFlight()) {
					window.draw(bullets[i].getShape());
				}
			}

			window.draw(player.getSprite());

			if (ammoPickup.isSpawned()) {
				window.draw(ammoPickup.getSprite());
			}

			if (healthPickup.isSpawned()) {
				window.draw(healthPickup.getSprite());
			}

			window.draw(spriteCrosshair);

			// Switch to HUD view
			window.setView(hudView);

			// draw hud
			window.draw(spriteAmmoIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(healthBar);
			window.draw(waveNumText);
			window.draw(zombiesRemainText);
		}

		if (state == State::LEVELING_UP) {
			window.draw(spriteGameOver);
			window.draw(levelUpText);
		}

		if (state == State::PAUSED) {
			window.draw(pausedText);
		}

		if (state == State::GAME_OVER) {
			window.draw(spriteGameOver);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(hiScoreText);
		}

		window.display();
	}

	// delete previously allocated memory
	delete[] zombies;

	return 0;
}