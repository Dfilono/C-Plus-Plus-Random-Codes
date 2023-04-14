#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

using namespace sf;

void updateBranches(int seed);

// Define Branches
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

// Player/Branch location
enum class side {LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES];


int main() {
	// Create video mode object
	VideoMode vm(1920, 1080);

	// Creat and open a window
	RenderWindow window(vm, "Timber!", Style::Fullscreen);

	// Create texture for background
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("graphics/background.png");

	// Creat sprite for background
	Sprite backgroundSprite;

	// Attach the texture to the sprite
	backgroundSprite.setTexture(backgroundTexture);

	// Set backgroundSprite to cover screen
	backgroundSprite.setPosition(0, 0);

	// Make tree sprite
	Texture treeTexture;
	treeTexture.loadFromFile("graphics/tree.png");
	Sprite treeSprite;
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(810, 0);

	// Make Bee sprite
	Texture beeTexture;
	beeTexture.loadFromFile("graphics/bee.png");
	Sprite beeSprite;
	beeSprite.setTexture(beeTexture);
	beeSprite.setPosition(0, 810);

	// Initialize Bee movement
	bool beeActive = false;
	float beeSpeed = 0.0f;

	// Make Cloud sprites
	Texture cloudTexture;
	cloudTexture.loadFromFile("graphics/cloud.png");
	Sprite cloudSprite1;
	Sprite cloudSprite2;
	Sprite cloudSprite3;
	cloudSprite1.setTexture(cloudTexture);
	cloudSprite2.setTexture(cloudTexture);
	cloudSprite3.setTexture(cloudTexture);
	cloudSprite1.setPosition(0, 0);
	cloudSprite2.setPosition(0, 250);
	cloudSprite3.setPosition(0, 500);

	// Initialize Cloud movement
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Prepare Branches
	Texture branchTexture;
	branchTexture.loadFromFile("graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(branchTexture);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}

	// Prepare Player
	Texture playerTexture;
	playerTexture.loadFromFile("graphics/player.png");
	Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(580, 720);
	side playerSide = side::LEFT;

	// Prepare gravestone
	Texture RIPTexture;
	RIPTexture.loadFromFile("graphics/rip.png");
	Sprite RIPSprite;
	RIPSprite.setTexture(RIPTexture);
	RIPSprite.setPosition(600, 860);

	// Pepare the axe
	Texture axeTexture;
	axeTexture.loadFromFile("graphics/axe.png");
	Sprite axeSprite;
	axeSprite.setTexture(axeTexture);
	axeSprite.setPosition(700, 830);

	// Line Axe up with tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	// Prepare log
	Texture logTexture;
	logTexture.loadFromFile("graphics/log.png");
	Sprite logSprite;
	logSprite.setTexture(logTexture);
	logSprite.setPosition(810, 720);
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	// Frame rate control
	Clock clock;

	// Check if game is paused
	bool paused = true;

	// Draw HUD
	// Init variables
	int score = 0;
	Text messageText;
	Text scoreText;
	Font font;
	// Set font
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);
	// Define strings
	messageText.setString("Press Enter to Start!");
	scoreText.setString("Score  = 0");
	// Set Size
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	// Set Color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	// Set Position
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	// Time Bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTotalTime;
	float timeRemains = 6.0f;
	float timeBarWidthPerSec = timeBarStartWidth / timeRemains;

	// player input
	bool acceptInput = false;

	// Prepare audio
	// chopping
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	// death
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	// Out of time
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound oot;
	oot.setBuffer(ootBuffer);

	while (window.isOpen()) {
		// Handle inputs
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased && !paused) {
				acceptInput = true;
				axeSprite.setPosition(2000, axeSprite.getPosition().y);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;
			score = 0;
			timeRemains = 6;

			// Make all branches disappear
			for (int i = 1; i < NUM_BRANCHES; i++) {
				branchPositions[i] = side::NONE;
			}

			// Hide grave
			RIPSprite.setPosition(675, 2000);

			// Move player into position
			playerSprite.setPosition(580, 720);

			acceptInput = true;
		}

		if (acceptInput) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				playerSide = side::RIGHT;
				score ++;
				// Increase time reamains based on score
				timeRemains += (2 / score) + 0.15;
				axeSprite.setPosition(AXE_POSITION_RIGHT, axeSprite.getPosition().y);
				playerSprite.setPosition(1200, 720);
				// update branches
				updateBranches(score);
				// send log flying
				logSprite.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;
				chop.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				playerSide = side::LEFT;
				score++;
				// Increase time reamains based on score
				timeRemains += (2 / score) + 0.15;
				axeSprite.setPosition(AXE_POSITION_LEFT, axeSprite.getPosition().y);
				playerSprite.setPosition(580, 720);
				// update branches
				updateBranches(score);
				// send log flying
				logSprite.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;
				chop.play();
			}
		}

		if (!paused) {
			// Update scene
			Time dt = clock.restart();

			// Subtract from time remaining
			timeRemains -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarWidthPerSec * timeRemains, timeBarHeight));

			// Reset game if time runs out
			if (timeRemains <= 0.0f) {
				paused = true;
				messageText.setString("Out of Time!");
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				oot.play();
			}

			// Setup bee movement
			if (!beeActive) {
				// Speed of Bee
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				// Position of Bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				beeSprite.setPosition(2000, height);

				beeActive = true;
			}
			else {
				// Move bee
				beeSprite.setPosition(beeSprite.getPosition().x - (beeSpeed * dt.asSeconds()), beeSprite.getPosition().y);

				// Check if the bee is still on screen
				if (beeSprite.getPosition().x < -100) {
					beeActive = false;
				}
			}

			// Setup cloud movement
			// Cloud 1
			if (!cloud1Active) {
				// Speed of cloud
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				// Position of cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				cloudSprite1.setPosition(-200, height);

				cloud1Active = true;
			}
			else {
				// Move cloud
				cloudSprite1.setPosition(cloudSprite1.getPosition().x + (cloud1Speed * dt.asSeconds()), cloudSprite1.getPosition().y);

				// Check if cloud still on screen
				if (cloudSprite1.getPosition().x > 1920) {
					cloud1Active = false;
				}
			}

			// Cloud 2
			if (!cloud2Active) {
				// Speed of cloud
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				// Position of cloud
				srand((int)time(0) * 20);
				float height = (rand() % 150);
				cloudSprite2.setPosition(-200, height);

				cloud2Active = true;
			}
			else {
				// Move cloud
				cloudSprite2.setPosition(cloudSprite2.getPosition().x + (cloud2Speed * dt.asSeconds()), cloudSprite2.getPosition().y);

				// Check if cloud still on screen
				if (cloudSprite2.getPosition().x > 1920) {
					cloud2Active = false;
				}
			}

			// Cloud 3
			if (!cloud3Active) {
				// Speed of cloud
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				// Position of cloud
				srand((int)time(0) * 30);
				float height = (rand() % 150);
				cloudSprite3.setPosition(-200, height);

				cloud3Active = true;
			}
			else {
				// Move cloud
				cloudSprite3.setPosition(cloudSprite3.getPosition().x + (cloud3Speed * dt.asSeconds()), cloudSprite3.getPosition().y);

				// Check if cloud still on screen
				if (cloudSprite3.getPosition().x > 1920) {
					cloud3Active = false;
				}
			}

			// Update Score
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			// Update branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;

				if (branchPositions[i] == side::LEFT) {
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT) {
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else {
					branches[i].setPosition(3000, height);
				}
			}

			// Animate flying log
			if (logActive) {
				logSprite.setPosition(logSprite.getPosition().x + (logSpeedX * dt.asSeconds()), logSprite.getPosition().y + (logSpeedY * dt.asSeconds()));

				// Has the log reached the edge
				if (logSprite.getPosition().x < -100 || logSprite.getPosition().x > 2000) {
					logActive = false;
					logSprite.setPosition(810, 720);
				}
			}

			// Collision with branch
			if (branchPositions[5] == playerSide) {
				// death
				paused = true;
				acceptInput = false;

				// grave
				RIPSprite.setPosition(525, 760);

				// hide player
				playerSprite.setPosition(2000, 760);

				// Change message text
				messageText.setString("SQUISHED!");
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				death.play();
			}
		}

		// Clear last frame
		window.clear();

		// Draw game
		window.draw(backgroundSprite);
		window.draw(cloudSprite1);
		window.draw(cloudSprite2);
		window.draw(cloudSprite3);

		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}

		window.draw(treeSprite);
		window.draw(playerSprite);
		window.draw(axeSprite);
		window.draw(logSprite);
		window.draw(RIPSprite);
		window.draw(beeSprite);

		// Draw Text
		window.draw(scoreText);

		// Draw Time Bar
		window.draw(timeBar);
		
		if (paused) {
			window.draw(messageText);
		}

		// Show everything drawn
		window.display();
	}

	return 0;
}

void updateBranches(int seed) {
	// Move branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}

	// Add new branch at position 0
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}