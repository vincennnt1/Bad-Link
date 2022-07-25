#include "Wall.h"

Wall::Wall(sf::Texture* text, sf::Vector2f pos)
{
	text->setSmooth(false);
	this->wall.setTexture(*text);

	this->wall.setPosition(pos);

	this->wall.setOrigin(text->getSize().x / 2.f, text->getSize().y / 2.f);
}

Wall::~Wall()
{
}

void Wall::render(sf::RenderTarget& target)
{
	target.draw(this->wall);
}

const sf::FloatRect Wall::getGlobalBounds() const
{
	return this->wall.getGlobalBounds();
}

const sf::Vector2f Wall::getPosition() const
{
	return this->wall.getPosition();
}
