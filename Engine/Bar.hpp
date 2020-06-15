#pragma once

#include "Libraries.hpp"

class Bar
{
private:

	sf::Vector2f size_;
	float fill_max;
	float fill;
	float percent;

	sf::RectangleShape filled_bar;
	sf::RectangleShape empty_bar;
	sf::RectangleShape outline;
	
public:
	Bar(sf::Color fill_color, sf::Color empty_color, sf::Vector2f size, sf::Vector2f position,float max,float current);
	virtual ~Bar();
	
	void update(float amount);
	void render(sf::RenderWindow* window);
	
};

