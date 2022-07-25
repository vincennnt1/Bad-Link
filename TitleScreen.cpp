#include "TitleScreen.h"



TitleScreen::TitleScreen(sf::Texture* text, sf::RenderWindow& window)
{
	this->sineX = 0.1f;

	this->logo = new sf::Sprite();

	text->setSmooth(false);
	this->logo->setTexture(*text);

	this->logo->setOrigin(text->getSize().x / 2.f, text->getSize().y / 2);
	this->logo->setPosition(sf::Vector2f(416, 300));

	this->font = new sf::Font();
	this->font->loadFromFile("Assets/Debug.otf");

	this->text = new sf::Text();

	this->text->setFont(*this->font);
	this->text->setPosition(sf::Vector2f(416, 700));
	this->text->setCharacterSize(60);
	this->text->setFillColor(sf::Color(177, 62, 83));
	this->text->setOutlineColor(sf::Color(41, 54, 111));
	this->text->setOutlineThickness(2);

	this->text->setString("Click To Play!");

	this->window = &window;

}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::run()
{
	while (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
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

		this->logo->move(sf::Vector2f(0, sin(this->sineX)));
		this->sineX += 0.1f;

		this->window->clear();

		this->window->draw(*this->logo);
		this->window->draw(*this->text);

		window->display();
	}

}
