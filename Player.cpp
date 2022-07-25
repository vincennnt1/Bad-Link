#include "Player.h"

Player::Player(sf::Texture* text, sf::Vector2f pos)
{
	text->setSmooth(false);
	this->player.setTexture(*text);

	this->player.setPosition(pos);

	this->player.setOrigin(text->getSize().x / 2.f, text->getSize().y / 2.f);

}

Player::~Player()
{
}

void Player::move(sf::Vector2f offset)
{
	this->player.move(offset);
}

void Player::setPosition(sf::Vector2f pos)
{
	this->player.setPosition(pos);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->player);

}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->player.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const
{
	return this->player.getPosition();
}
