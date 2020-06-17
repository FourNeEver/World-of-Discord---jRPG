#pragma once

#include "Libraries.hpp"

class Bar
{
private:

	sf::Vector2f size_;
	sf::Vector2f offset_;
	float fill_max;
	float fill;
	float change = 0;
	bool isVertical;
	
	sf::RectangleShape filled_bar;
	sf::RectangleShape empty_bar;
	sf::RectangleShape outline;
	
public:
	Bar(sf::Color fill_color, sf::Color empty_color, sf::Vector2f size, sf::FloatRect origin, sf::Vector2f offset, float max, float current, bool isVertical);
	virtual ~Bar();
	
	void update(float amount);
	void render(sf::RenderWindow* window);

	void update_origin(sf::FloatRect origin);
};

              