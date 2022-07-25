#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>


class Hole
{
private:
	sf::Sprite hole;

public:
	Hole(sf::Texture* text, sf::Vector2f pos, bool isGood);
	virtual~Hole();

	bool isGood;

	// FUNCTIONS
	void render(sf::RenderTarget& target);

	// accessors
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;
};

