#pragma once
#pragma once
#include "../../Libraries.hpp"
#include "../Bar.hpp";

struct GUI
{
	Bar health_bar { sf::Color::Green, sf::Color::Red, sf::Vector2f(0, 0), sf::FloatRect(0,0,0,0),sf::Vector2f(10,0), 1, 1,true };
};