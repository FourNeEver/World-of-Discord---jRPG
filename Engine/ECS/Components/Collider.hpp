#pragma once
#pragma once
#include "../../Libraries.hpp"

struct Collider
{
	std::string flag;
	float hight;
	float widht;
	sf::FloatRect hitbox;
	std::map<std::string, bool> colliding;
};