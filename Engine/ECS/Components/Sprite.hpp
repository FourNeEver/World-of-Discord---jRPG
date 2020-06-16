#pragma once
#include "../../Libraries.hpp"

struct Sprite
{
	sf::Texture texture;
	sf::IntRect sprite_rect;
	bool isVisible;
	sf::Sprite sprite;
};
