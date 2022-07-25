#include "Hole.h"

Hole::Hole(sf::Texture* text, sf::Vector2f pos, bool isGood)
{
	this->isGood = isGood;

	text->setSmooth(false);
	this->hole.setTexture(*text);

	this->hole.setOrigin(text->getSize().x / 2.f, text->getSize().y / 2.f);

	this->hole.setPosition(pos);
}

Hole::~Hole()
{
}

void Hole::render(sf::RenderTarget& target)
{
	target.draw(this->hole);
}

const sf::FloatRect Hole::getGlobalBounds() const
{
	return this->hole.getGlobalBounds();
}

const sf::Vector2f Hole::getPosition() const
{
	return this->hole.getPosition();
}
