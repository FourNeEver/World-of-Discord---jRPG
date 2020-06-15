#include "Bar.hpp"

Bar::Bar(sf::Color fill_color, sf::Color empty_color, sf::Vector2f size, sf::Vector2f position, float max, float current)
	: size_(size),fill_max(max),fill(current)
{
	filled_bar.setSize(size_);
	filled_bar.setPosition(position);
	filled_bar.setFillColor(fill_color);

	empty_bar.setSize(size_);
	empty_bar.setPosition(position);
	empty_bar.setFillColor(empty_color);

	outline.setSize(sf::Vector2f(size_.x+2,size_.y+2));
	outline.setPosition(sf::Vector2f(position.x-1,position.y-1));
	outline.setOutlineColor(sf::Color::Black);
	outline.setOutlineThickness(1);

	filled_bar.setSize(sf::Vector2f(size_.x * (fill/fill_max), size_.y));
	
}

Bar::~Bar()
{
	
}

void Bar::update(float amount)
{
	fill = amount;
	
	if (fill < 0)
		fill = 0;
	if (fill > fill_max)
		fill = fill_max;
	
	filled_bar.setSize(sf::Vector2f(size_.x * (fill / fill_max), size_.y));
}

void Bar::render(sf::RenderWindow* window)
{
	window->draw(outline);
	window->draw(empty_bar);
	window->draw(filled_bar);
}
