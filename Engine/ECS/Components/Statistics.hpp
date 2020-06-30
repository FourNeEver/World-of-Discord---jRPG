#pragma once
#include "../../Libraries.hpp"
//enum FLAG { ENEMY, ALLY };


struct Statistics
{
	std::string name;
	std::string race;
	int level;
	int expirence;
	int max_expierence;
	
	int health;
	int max_health;
	int strenght;
	int luck;
	int magic;
	int defense;
	int resistance;
	
	std::string flag;

	std::vector<int> abilities;
	
	bool alive = true;
};
