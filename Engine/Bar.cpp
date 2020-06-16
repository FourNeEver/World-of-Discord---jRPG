#include "Bar.hpp"

Bar::Bar(sf::Color fill_color, sf::Color empty_color, sf::Vector2f size, sf::FloatRect origin, sf::Vector2f offset, float max, float current, bool isVert)
	: size_(size),fill_max(max),fill(current),isVertical(isVert)
{
	filled_bar.setSize(size_);
	filled_bar.setFillColor(fill_color);
	if (isVertical)
	{
		filled_bar.setPosition(sf::Vector2f(origin.left + origin.width + offset.x, origin.top + origin.height / 2 - filled_bar.getSize().y / 2 + offset.y));
	}
	else
		filled_bar.setPosition(sf::Vector2f(origin.left + origin.width / 2 - filled_bar.getSize().x / 2 + offset.x, origin.top + origin.height + offset.y));

	empty_bar.setSize(filled_bar.getSize());
	empty_bar.setPosition(filled_bar.getPosition());
	empty_bar.setFillColor(empty_color);

	outline.setSize(sf::Vector2f(filled_bar.getSize().x+2,filled_bar.getSize().y+2));
	outline.setPosition(sf::Vector2f(filled_bar.getPosition().x-1,filled_bar.getPosition().y-1));
	outline.setOutlineColor(sf::Color::Black);
	outline.setOutlineThickness(1);

	filled_bar.setSize(sf::Vector2f(size_.x * (fill/fill_max), size_.y));
	if (isVertical)
	{
		filled_bar.rotate(180);
		empty_bar.rotate(180);
		outline.rotate(180);
		filled_bar.move(sf::Vector2f(0, filled_bar.getSize().y));
		empty_bar.move(sf::Vector2f(0, empty_bar.getSize().y));
		outline.move(sf::Vector2f(2, outline.getSize().y));
	}
	
}

Bar::~Bar()
{
	
}

void Bar::update(float amount)
{
	change = fill;
	fill = amount;
	if (fill < 0)
		fill = 0;
	if (fill > fill_max)
		fill = fill_max;

	if (isVertical)
	{
		filled_bar.setSize(sf::Vector2f(size_.x, size_.y * (change / fill_max)));
	}
	else
		filled_bar.setSize(sf::Vector2f(size_.x * (change / fill_max), size_.y));
	
	if (change > fill)
		change *= 0.99;
	if (change<fill)
		change *= 1.01;
	if (abs(change - fill) < 0.1)
		fill = change;
}

void Bar::render(sf::RenderWindow* window)
{
	window->draw(outline);
	window->draw(empty_bar);
	window->draw(filled_bar);
}
