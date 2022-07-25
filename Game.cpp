#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(832, 896), "Bad Link", sf::Style::Close);
	this->window->setFramerateLimit(60);

	this->displayTutorial = true; // CHANGE BACK TO TRUE
}

void Game::initTextures()
{
	// TILE BKG
	this->textures["TILES"] = new sf::Texture();
	this->textures["TILES"]->loadFromFile("Textures/tiles.png");

	// GOOD PLAYER
	this->textures["GOODPLAYER"] = new sf::Texture();
	this->textures["GOODPLAYER"]->loadFromFile("Textures/goodPlayer.png");

	// BAD PLAYER
	this->textures["BADPLAYER"] = new sf::Texture();
	this->textures["BADPLAYER"]->loadFromFile("Textures/badPlayer.png");

	// WAlLS
	this->textures["WALL"] = new sf::Texture();
	this->textures["WALL"]->loadFromFile("Textures/wall.png");

	// CHECKMARK
	this->textures["CHECKMARK"] = new sf::Texture();
	this->textures["CHECKMARK"]->loadFromFile("Textures/checkmark.png");

	// EX
	this->textures["EX"] = new sf::Texture();
	this->textures["EX"]->loadFromFile("Textures/ex.png");

	// LOGO
	this->textures["LOGO"] = new sf::Texture();
	this->textures["LOGO"]->loadFromFile("Textures/logo.png");
}

void Game::initBackground()
{
	// GOOD ONE
	this->goodBackground = new sf::Sprite;
	this->goodBackground->setTexture(*this->textures["TILES"]);
	this->goodBackground->setOrigin(sf::Vector2f(this->goodBackground->getTexture()->getSize().x / 2.f, this->goodBackground->getTexture()->getSize().y / 2.f));
	this->goodBackground->setPosition(sf::Vector2f(224, 448));
	this->goodBackground->setScale(2.f, 2.f);

	// BAD ONE
	this->badBackground = new sf::Sprite;
	this->badBackground->setTexture(*this->textures["TILES"]);
	this->badBackground->setOrigin(sf::Vector2f(this->badBackground->getTexture()->getSize().x / 2.f, this->badBackground->getTexture()->getSize().y / 2.f));
	this->badBackground->setPosition(sf::Vector2f(608, 448));
	this->badBackground->setScale(2.f, 2.f);
}

void Game::initPlayers()
{
	// GOOD ONE
	this->goodPlayer = new Player(this->textures["GOODPLAYER"], sf::Vector2f(240, 592));

	// BAD ONE
	this->badPlayer = new Player(this->textures["BADPLAYER"], sf::Vector2f(624, 592));

	this->movement = 32.f;
}

void Game::initClock()
{
	this->moveTimer = new sf::Clock;
}

void Game::initFont()
{
	this->font = new sf::Font;
	this->font->loadFromFile("Assets/Debug.otf");
}

void Game::initSound()
{
	// LEVEL COMPLETE
	this->levelCompleted = false;

	this->levelCompleteBuffer = new sf::SoundBuffer;
	this->levelCompleteBuffer->loadFromFile("Assets/levelComplete.wav");

	this->levelComplete = new sf::Sound;
	this->levelComplete->setBuffer(*this->levelCompleteBuffer);

	// MOVE
	this->moved = false;

	this->moveSoundBuffer = new sf::SoundBuffer;
	this->moveSoundBuffer->loadFromFile("Assets/move.wav");

	this->moveSound = new sf::Sound;
	this->moveSound->setBuffer(*this->moveSoundBuffer);
	this->moveSound->setVolume(50);


}

void Game::titleScreen()
{
	this->title = new TitleScreen(this->textures["LOGO"], *this->window);
	this->title->run();
	delete this->title;
}

void Game::initLevel() // MAKE IT -/+ 16
{
	// LEVL
	this->levelText = new sf::Text;
	this->levelText->setFont(*this->font);
	this->levelText->setCharacterSize(50);
	this->levelText->setPosition(350.f, 50.f);

	switch (level)
	{
	case 1: // LEVEL 1
		// GOOD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(240, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 400)));

		// BAD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(592, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(592, 400)));

		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(240, 400), true)); // good side
		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(560, 528), true)); // bad side

		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(208, 464), false)); // good side
		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(592, 560), false)); // bad side

		// LEVEL TEXT
		this->levelText->setString("Level 1");


		// TUTORIAL
		if (displayTutorial)
		{
			// CLOCK
			this->tempTutorialTime = new sf::Clock;

			this->tutorialText1 = new sf::Text;
			this->tutorialText1->setFont(*this->font);
			this->tutorialText1->setCharacterSize(50);
			this->tutorialText1->setPosition(208.f, 0.f);
			this->tutorialText1->setString("Welcome to Bad Link!");

			this->tutorialText2 = new sf::Text;
			this->tutorialText2->setFont(*this->font);
			this->tutorialText2->setCharacterSize(19);
			this->tutorialText2->setPosition(10.f, 75.f);
			this->tutorialText2->setString("Your goal is to get both the \nangry and the happy player to the \ncheckmark at the same time. \nHowever, if only one of them \ntouch it, you must restart.");

			this->tutorialText3 = new sf::Text;
			this->tutorialText3->setFont(*this->font);
			this->tutorialText3->setCharacterSize(19);
			this->tutorialText3->setPosition(510.f, 75.f);
			this->tutorialText3->setString("Your angry player is currently\nin the bad place. You must \nget him to the good place. To do this, \nyou must avoid the \nXs or you will have to restart.");

			this->tutorialText4 = new sf::Text;
			this->tutorialText4->setFont(*this->font);
			this->tutorialText4->setCharacterSize(50);
			this->tutorialText4->setPosition(175.f, 750.f);
			this->tutorialText4->setString("Left Click to Exit Tutorial!");

		}

		break;

	case 2: // LEVEL 2
		// clear everything
		this->walls.clear();
		this->goodHoles.clear();
		this->badHoles.clear();

		// GOOD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 208)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 240)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 272)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 336)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 400)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 432)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 496)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 528)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 592)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 624)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 656)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 688)));

		// BAD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 208)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 240)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 304)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 336)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 400)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 432)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 496)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 528)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 592)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 624)));


		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(112, 208), true)); // good side
		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(496, 208), true)); // bad side

		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(112, 272), false)); // good side
		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(560, 656), false)); // bad side

		// Level text
		this->levelText->setString("Level 2");

		break;

	case 3: // LEVEL 3
		// clear everything
		this->walls.clear();
		this->goodHoles.clear();
		this->badHoles.clear();


		this->badPlayer->move(sf::Vector2f(0, 64));
		this->goodPlayer->move(sf::Vector2f(0, 64));

		// GOOD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(208, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(240, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(304, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(336, 272)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(112, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(144, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(208, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(240, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 368)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(208, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(240, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(304, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(336, 464)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(112, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(144, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(208, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(240, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 560)));

		// BAD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(592, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(624, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(656, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(688, 272)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(720, 272)));
		
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(496, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(528, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(592, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(624, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(656, 368)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(592, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(624, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(656, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(688, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(720, 464)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(496, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(528, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(592, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(624, 560)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(656, 560)));

		// HOLES
		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(336, 240), true)); // good side
		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(720, 208), true)); // bad side

		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(240, 208), false)); // good side
		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(624, 240), false)); // bad side

		// Level text
		this->levelText->setString("Level 3");
		break;


	case 4: // LEVEL 4
	// clear everything
		this->walls.clear();
		this->goodHoles.clear();
		this->badHoles.clear();

		// GOOD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(208, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(240, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 368)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 400)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 432)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 464)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(208, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(240, 464)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 432)));

		// BAD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(528, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(592, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(624, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(656, 368)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(656, 400)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(656, 432)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(656, 464)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(592, 464)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(624, 464)));

		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 432)));

		// HOLES
		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(208, 432), true)); // good side
		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(624, 432), true)); // bad side

		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(240, 432), false)); // good side
		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(592, 432), false)); // bad side

		// Level text
		this->levelText->setString("Level 4");
		break;

	case 5: // LEVEL 5
		// clear everything
		this->walls.clear();
		this->goodHoles.clear();
		this->badHoles.clear();

		// GOOD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(336, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(304, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(272, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(240, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(208, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(176, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(144, 368)));

		// BAD WALLS
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(688, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(656, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(624, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(592, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(560, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(528, 368)));
		this->walls.push_back(new Wall(this->textures["WALL"], sf::Vector2f(496, 368)));

		// HOLES
		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(304, 336), true)); // good side
		this->goodHoles.push_back(new Hole(this->textures["CHECKMARK"], sf::Vector2f(688, 208), true)); // bad side

		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(304, 208), false)); // good side
		this->badHoles.push_back(new Hole(this->textures["EX"], sf::Vector2f(688, 336), false)); // bad side

		// Level text
		this->levelText->setString("Level 5");
		break;

	case 6:
		// clear everything from memory
		this->walls.clear();
		this->goodHoles.clear();
		this->badHoles.clear();
		this->finished = true;

		this->levelText->setPosition(200.f, 450.f);
		this->levelText->setCharacterSize(80.f);
		this->levelText->setString("You have finished!");

	}
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initBackground();
	this->initPlayers();
	this->initClock();
	this->initFont();
	this->initSound();

	this->titleScreen();

	this->initLevel();
}

Game::~Game()
{
	delete this->window;

	// backgrounds
	delete this->badBackground;
	delete this->goodBackground;

	// players
	delete this->goodPlayer;
	delete this->badPlayer;

	// font
	delete this->font;

	// sounds
	delete this->levelComplete;
	delete this->levelCompleteBuffer;
	delete this->moveSoundBuffer;
	delete this->moveSound;

	// deleting textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	// deleting walls
	for (auto* i : this->walls)
	{
		delete i;
	}

	// deleting good holes
	for (auto* i : this->goodHoles)
	{
		delete i;
	}

	// deleting bad holes
	for (auto* i : this->badHoles)
	{
		delete i;
	}

	// tutorial texts
	delete this->tutorialText1;
	delete this->tutorialText2;
	delete this->tutorialText3;
	delete this->tutorialText4;
}

void Game::updatePollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			this->window->close();

		if (ev.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				this->window->close();
		}
	}
}

void Game::updateInput()
{
	sf::Time elapsed = this->moveTimer->getElapsedTime();
	if (!finished) {
		if (elapsed.asMilliseconds() >= 200.f)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  // UP
			{
				this->goodVelocity.y = -1 * movement;
				this->badVelocity.y = -1 * movement;

				this->moveTimer->restart();

				this->moved = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  // DOWN
			{
				this->goodVelocity.y = 1 * movement;
				this->badVelocity.y = 1 * movement;

				this->moveTimer->restart();

				this->moved = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  // RIGHT
			{
				this->goodVelocity.x = 1 * movement;
				this->badVelocity.x = 1 * movement;

				this->moveTimer->restart();

				this->moved = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  // LEFT
			{
				this->goodVelocity.x = -1 * movement;
				this->badVelocity.x = -1 * movement;

				this->moveTimer->restart();

				this->moved = true;
			}
		}
	}
}

void Game::updateBorderCollision()
{
	if (!finished) {
		// Good Player
		this->goodPlayerBounds = this->goodPlayer->getGlobalBounds();
		this->goodNextPos = this->goodPlayerBounds;
		this->goodNextPos.left += goodVelocity.x;
		this->goodNextPos.top += goodVelocity.y;

		if (this->goodNextPos.left <= this->goodBackground->getGlobalBounds().left) { // left side of player
			this->goodVelocity.x = 0;
		}
		else if (this->goodNextPos.left + this->goodNextPos.width >= this->goodBackground->getGlobalBounds().left + this->goodBackground->getGlobalBounds().width) { // right side of player
			this->goodVelocity.x = 0;
		}
		if (this->goodNextPos.top <= this->goodBackground->getGlobalBounds().top) { // top side of player
			this->goodVelocity.y = 0;
		}
		else if (this->goodNextPos.top + this->goodNextPos.height >= this->goodBackground->getGlobalBounds().top + this->goodBackground->getGlobalBounds().height) { // left side of player
			this->goodVelocity.y = 0;
		}

		// Bad Player
		this->badPlayerBounds = this->badPlayer->getGlobalBounds();
		this->badNextPos = this->badPlayerBounds;
		this->badNextPos.left += badVelocity.x;
		this->badNextPos.top += badVelocity.y;

		if (this->badNextPos.left <= this->badBackground->getGlobalBounds().left) { // left side of player
			this->badVelocity.x = 0;
		}
		else if (this->badNextPos.left + this->badNextPos.width >= this->badBackground->getGlobalBounds().left + this->badBackground->getGlobalBounds().width) { // right side of player
			this->badVelocity.x = 0;
		}
		if (this->badNextPos.top <= this->badBackground->getGlobalBounds().top) { // top side of player
			this->badVelocity.y = 0;
		}
		else if (this->badNextPos.top + this->badNextPos.height >= this->badBackground->getGlobalBounds().top + this->badBackground->getGlobalBounds().height) { // left side of player
			this->badVelocity.y = 0;
		}
	}
}

void Game::updateWallCollision()
{
	if (!finished) {
		for (auto& wall : this->walls)
		{


			this->goodPlayerBounds = this->goodPlayer->getGlobalBounds();
			this->badPlayerBounds = this->badPlayer->getGlobalBounds();
			this->wallBounds = wall->getGlobalBounds();

			this->goodNextPos = this->goodPlayerBounds;
			this->goodNextPos.left += goodVelocity.x;
			this->goodNextPos.top += goodVelocity.y;

			this->badNextPos = this->badPlayerBounds;
			this->badNextPos.left += badVelocity.x;
			this->badNextPos.top += badVelocity.y;

			if (this->wallBounds.intersects(this->goodNextPos)) // GOOD PLAYER
			{

				// BOTTOM COLLISION
				if (this->goodPlayerBounds.top < this->wallBounds.top
					&& this->goodPlayerBounds.top + goodPlayerBounds.height < this->wallBounds.top + this->wallBounds.height
					&& this->goodPlayerBounds.left < this->wallBounds.left + this->wallBounds.width
					&& this->goodPlayerBounds.left + this->goodPlayerBounds.width > this->wallBounds.left)
				{
					goodVelocity.y = 0.f;
					this->goodPlayer->setPosition(sf::Vector2f(this->goodPlayer->getPosition().x, this->goodPlayer->getPosition().y + (this->wallBounds.top - (this->goodPlayerBounds.top + this->goodPlayerBounds.height))));
				}

				// TOP COLLISION
				else if (this->goodPlayerBounds.top > this->wallBounds.top
					&& this->goodPlayerBounds.top + goodPlayerBounds.height > this->wallBounds.top + this->wallBounds.height
					&& this->goodPlayerBounds.left < this->wallBounds.left + this->wallBounds.width
					&& this->goodPlayerBounds.left + this->goodPlayerBounds.width > this->wallBounds.left)
				{
					goodVelocity.y = 0.f;
					this->goodPlayer->setPosition(sf::Vector2f(this->goodPlayer->getPosition().x, this->goodPlayer->getPosition().y - (this->goodPlayerBounds.top - (this->wallBounds.top + this->wallBounds.height))));

				}

				// RIGHT COLLISION
				if (this->goodPlayerBounds.left < this->wallBounds.left
					&& this->goodPlayerBounds.left + goodPlayerBounds.width < this->wallBounds.left + this->wallBounds.width
					&& this->goodPlayerBounds.top < this->wallBounds.top + this->wallBounds.height
					&& this->goodPlayerBounds.top + this->goodPlayerBounds.height > this->wallBounds.top)
				{
					goodVelocity.x = 0.f;
					this->goodPlayer->setPosition(sf::Vector2f(this->goodPlayer->getPosition().x + (this->wallBounds.left - (this->goodPlayerBounds.left + this->goodPlayerBounds.width)), this->goodPlayer->getPosition().y));
				}

				// LEFT COLLISION
				else if (this->goodPlayerBounds.left > this->wallBounds.left
					&& this->goodPlayerBounds.left + goodPlayerBounds.width > this->wallBounds.left + this->wallBounds.width
					&& this->goodPlayerBounds.top < this->wallBounds.top + this->wallBounds.height
					&& this->goodPlayerBounds.top + this->goodPlayerBounds.height > this->wallBounds.top)
				{
					goodVelocity.x = 0.f;
					this->goodPlayer->setPosition(sf::Vector2f(this->goodPlayer->getPosition().x - (this->goodPlayerBounds.left - (this->wallBounds.left + this->wallBounds.width)), this->goodPlayer->getPosition().y));

				}



			}


			if (this->wallBounds.intersects(this->badNextPos)) // BAD PLAYER
			{

				// BOTTOM COLLISION
				if (this->badPlayerBounds.top < this->wallBounds.top
					&& this->badPlayerBounds.top + badPlayerBounds.height < this->wallBounds.top + this->wallBounds.height
					&& this->badPlayerBounds.left < this->wallBounds.left + this->wallBounds.width
					&& this->badPlayerBounds.left + this->badPlayerBounds.width > this->wallBounds.left)
				{
					badVelocity.y = 0.f;
					this->badPlayer->setPosition(sf::Vector2f(this->badPlayer->getPosition().x, this->badPlayer->getPosition().y + (this->wallBounds.top - (this->badPlayerBounds.top + this->badPlayerBounds.height))));

				}

				// TOP COLLISION
				else if (this->badPlayerBounds.top > this->wallBounds.top
					&& this->badPlayerBounds.top + badPlayerBounds.height > this->wallBounds.top + this->wallBounds.height
					&& this->badPlayerBounds.left < this->wallBounds.left + this->wallBounds.width
					&& this->badPlayerBounds.left + this->badPlayerBounds.width > this->wallBounds.left)
				{
					badVelocity.y = 0.f;
					this->badPlayer->setPosition(sf::Vector2f(this->badPlayer->getPosition().x, this->badPlayer->getPosition().y - (this->badPlayerBounds.top - (this->wallBounds.top + this->wallBounds.height))));

				}

				// RIGHT COLLISION
				if (this->badPlayerBounds.left < this->wallBounds.left
					&& this->badPlayerBounds.left + badPlayerBounds.width < this->wallBounds.left + this->wallBounds.width
					&& this->badPlayerBounds.top < this->wallBounds.top + this->wallBounds.height
					&& this->badPlayerBounds.top + this->badPlayerBounds.height > this->wallBounds.top)
				{
					badVelocity.x = 0.f;
					this->badPlayer->setPosition(sf::Vector2f(this->badPlayer->getPosition().x + (this->wallBounds.left - (this->badPlayerBounds.left + this->badPlayerBounds.width)), this->badPlayer->getPosition().y));

				}

				// LEFT COLLISION
				else if (this->badPlayerBounds.left > this->wallBounds.left
					&& this->badPlayerBounds.left + badPlayerBounds.width > this->wallBounds.left + this->wallBounds.width
					&& this->badPlayerBounds.top < this->wallBounds.top + this->wallBounds.height
					&& this->badPlayerBounds.top + this->badPlayerBounds.height > this->wallBounds.top)
				{
					badVelocity.x = 0.f;
					this->badPlayer->setPosition(sf::Vector2f(this->badPlayer->getPosition().x - (this->badPlayerBounds.left - (this->wallBounds.left + this->wallBounds.width)), this->badPlayer->getPosition().y));
				}



			}
		}
	}
}

void Game::updateLevel()
{
	if (!finished) {
		// TUTORIAL
		if (displayTutorial)
		{
			sf::Time elapse = this->tempTutorialTime->getElapsedTime();
			if (elapse.asMilliseconds() >= 500)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->displayTutorial = false;

				}
			}
		}

		for (int i = 0; i < this->badHoles.size(); i++) // BAD HOLES
		{
			if (this->goodPlayer->getGlobalBounds().intersects(this->badHoles[i]->getGlobalBounds()) || this->badPlayer->getGlobalBounds().intersects(this->badHoles[i]->getGlobalBounds()))
			{
				delete this->badPlayer;
				delete this->goodPlayer;

				this->initPlayers();
				this->badVelocity = sf::Vector2f(0, 0);
				this->goodVelocity = sf::Vector2f(0, 0);
			}
		}

		// GOOD HOLES

		if (this->goodPlayer->getGlobalBounds().intersects(this->goodHoles[0]->getGlobalBounds()) && this->badPlayer->getGlobalBounds().intersects(this->goodHoles[1]->getGlobalBounds())) // COMPLETED
		{
			delete this->badPlayer;
			delete this->goodPlayer;

			this->initPlayers();
			this->badVelocity = sf::Vector2f(0, 0);
			this->goodVelocity = sf::Vector2f(0, 0);

			this->level++;
			this->initLevel();
			this->levelCompleted = true;
		}

		else if (this->goodPlayer->getGlobalBounds().intersects(this->goodHoles[0]->getGlobalBounds()) || this->badPlayer->getGlobalBounds().intersects(this->goodHoles[1]->getGlobalBounds()))
		{
			delete this->badPlayer;
			delete this->goodPlayer;

			this->initPlayers();
			this->badVelocity = sf::Vector2f(0, 0);
			this->goodVelocity = sf::Vector2f(0, 0);
		}
	}
}

void Game::updateSound()
{
	if (!finished) {
		if (this->levelCompleted)
		{
			this->levelComplete->play();
			this->levelCompleted = false;
			this->moved = false;
			this->moveSound->setVolume(0);
		}

		if (!this->levelCompleted)
		{
			if (this->moved)
			{
				this->moveSound->play();
				this->moved = false;
			}
		}

		this->moveSound->setVolume(50);
	}
}


void Game::updateMovement()
{
	if (!finished) {
		this->goodPlayer->move(this->goodVelocity);
		this->badPlayer->move(this->badVelocity);

		this->goodVelocity.x = 0;
		this->goodVelocity.y = 0;

		this->badVelocity.x = 0;
		this->badVelocity.y = 0;
	}
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->updateBorderCollision();
	this->updateWallCollision();
	this->updateLevel();
	this->updateSound();
	this->updateMovement();
}

void Game::render()
{
	this->window->clear(sf::Color(45, 45, 45));

	// TUTORIAL
	if (displayTutorial)
	{
		this->window->draw(*this->tutorialText1);
		this->window->draw(*this->tutorialText2);
		this->window->draw(*this->tutorialText3);
		this->window->draw(*this->tutorialText4);
	}
	else {
		this->window->draw(*this->levelText);
	}

	if (!finished) {
		// tile backgrounds
		this->window->draw(*this->goodBackground);
		this->window->draw(*this->badBackground);

		// PLAYERS
		this->goodPlayer->render(*this->window);
		this->badPlayer->render(*this->window);

		// WALLS
		for (int i = 0; i < this->walls.size(); i++)
		{
			this->walls[i]->render(*this->window);
		}

		// Good Holes
		for (int i = 0; i < this->goodHoles.size(); i++)
		{
			this->goodHoles[i]->render(*this->window);
		}

		// Bad Holes
		for (int i = 0; i < this->badHoles.size(); i++)
		{
			this->badHoles[i]->render(*this->window);
		}
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen()) {

		this->update();

		this->render();
	}
}
