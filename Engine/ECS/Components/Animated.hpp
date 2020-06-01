#pragma once
#include "../../Libraries.hpp"
#include "../../Animation.hpp"

struct Animated
{
	std::string currentAnimation;
	const char* path;
	std::map<std::string, Animation*> animations {};
};
