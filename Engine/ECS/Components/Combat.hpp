#include "../../Libraries.hpp"

struct Combat
{
	bool in_combat = false;
	int opponent_ID = NULL;
	bool is_initialized = false;
	sf::Vector2f pre_battle_position;
};