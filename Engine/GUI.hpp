#pragma once
#include "Libraries.hpp"
#include "ECS/ECS.hpp"
#include "Button.hpp"
#include "Bar.hpp"

class BattleGUI
{
	sf::RectangleShape background;
	sf::Texture texture_background;
	std::list<Entity*> heroes_list;


public:
	BattleGUI(sf::RenderWindow& window, sf::Texture& background_tex, std::list<Entity*> entites);
	
	
};

