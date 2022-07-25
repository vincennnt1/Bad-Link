#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Wall
{
private:
	sf::Sprite wall;

public:
	Wall(sf::Texture* text, sf::Vector2f pos);
	virtual~Wall();

	// FUNCTIONS
	void render(sf::RenderTarget& target);

	// accessors
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;
};

