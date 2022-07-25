#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Player
{
private:
	sf::Sprite player;


public:

	Player(sf::Texture* text, sf::Vector2f pos);
	virtual ~Player();

	// FUNCTIONS

	void move(sf::Vector2f offset);
	void setPosition(sf::Vector2f pos);
	void render(sf::RenderTarget& target);

	// accessors
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;
};

