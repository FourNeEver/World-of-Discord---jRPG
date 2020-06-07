#pragma once
#include "../../Libraries.hpp"

struct Collider
{
	std::string flag;
	float hight;
	float widht;
	sf::Vector2f offset = sf::Vector2f(0,0);
	sf::FloatRect hitbox;
	std::map<std::string, bool> colliding;
};