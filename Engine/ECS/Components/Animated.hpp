#pragma once
#include "../../Libraries.hpp"
#include "../../Animation.hpp"

struct Animated
{
	sf::Texture texture_sheet;
	std::string currentAnimation;
	const char* path;
	std::map<std::string, Animation*> animations {};
};
