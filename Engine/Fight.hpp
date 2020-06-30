#pragma once
#include <string>
#include <vector>

struct Cost
{
	std::string statistic;
	float flat_value;
	float percent;
};

struct Modifire
{
	std::string origin;
	std::string statistic;
	float percent;
};

struct Effect
{
	std::string type;
	std::string target;
	int duration;
	float flat_value;
	std::vector<Modifire> modifires;
	std::pair<float, float> critical;
};

struct Ability
{
	std::string name;
	std::string target;
	std::vector<Effect> effects;
	int casts;
	std::vector<Cost> costs;
	int particle_ID;
};
