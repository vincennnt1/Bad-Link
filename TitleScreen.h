#pragma once

#include <SFML/Graphics.hpp>

#include <math.h>

class TitleScreen
{
private:
	sf::Sprite* logo;

	sf::Font* font;

	sf::Text* text;

	sf::RenderWindow* window;

	float sineX;

public:
	TitleScreen(sf::Texture* text, sf::RenderWindow& window);
	virtual ~TitleScreen();


	void run();

};