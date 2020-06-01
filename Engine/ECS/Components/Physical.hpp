#pragma once
#include "../../Libraries.hpp"

struct Physical
{
	sf::Vector2f velocity;
	float acceleration;
	float deceleration;
	float maxVelocity;
	sf::Vector2f direction;
	bool isIdle;
	sf::Vector2f move_predict;
};


