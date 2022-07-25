#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <vector>
#include <iostream>

#include "Player.h"
#include "Wall.h"
#include "Hole.h"
#include "TitleScreen.h"

class Game
{
private:
	sf::RenderWindow* window;

	// resources
	std::map<std::string, sf::Texture*> textures;

	// walls
	std::vector<Wall*> walls;

	// tile backgrounds
	sf::Sprite* goodBackground;
	sf::Sprite* badBackground;

	// PLAYERS
	Player* goodPlayer;
	Player* badPlayer;

	// HOLES
	std::vector <Hole*> goodHoles;
	std::vector <Hole*> badHoles;

	sf::Vector2f goodVelocity;
	sf::Vector2f badVelocity;
	float movement;

	sf::Clock* moveTimer;

	// collision
	sf::FloatRect goodNextPos;
	sf::FloatRect badNextPos;

	sf::FloatRect goodPlayerBounds;
	sf::FloatRect badPlayerBounds;

	sf::FloatRect wallBounds;

	// AUDIO
	sf::SoundBuffer* levelCompleteBuffer;
	sf::Sound* levelComplete;

	sf::SoundBuffer* moveSoundBuffer;
	sf::Sound* moveSound;

	bool levelCompleted;
	bool moved;

	// TITLESCREEN
	TitleScreen* title;

	// FUNCTIONS
	void initWindow(); // INIT WINDOW
	void initTextures(); // INIT TEXTURES
	void initBackground(); // INIT BACKGROUND
	void initPlayers(); // INIT PLAYERS
	void initClock(); // INIT CLOCK
	void initFont(); // INIT FONT
	void initSound(); // INIT SOUND

	void titleScreen(); // TITLESCREEN

	void initLevel(); // INIT LEVELS
	int level = 1; // CURRENT LEVEL
	sf::Text* levelText;

	bool finished = false;


	sf::Font* font;
	sf::Text* tutorialText1;
	sf::Text* tutorialText2;
	sf::Text* tutorialText3;
	sf::Text* tutorialText4;
	bool displayTutorial;

	sf::Clock* tempTutorialTime;

public:

	// CONSTRUCTOR & DECONSTRUCTOR
	Game();
	virtual ~Game();

	// FUNCTIONS
	void update();
	void render();

	void updatePollEvents();
	void updateInput();
	void updateMovement();
	void updateBorderCollision();
	void updateWallCollision();
	void updateLevel();
	void updateSound();

	void run();
};

