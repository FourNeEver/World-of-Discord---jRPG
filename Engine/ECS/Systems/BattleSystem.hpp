#pragma once

#include "../Components.hpp"
#include "../Core/Coordinator.hpp"

class BattleSystem
	:public System
{
public:

	
	void battle(Coordinator* coordinator, Entity* player, Entity* enemy, sf::RenderWindow* window)
	{
		auto& p_stats = coordinator->GetComponent<Statistics>(*player);
		auto& e_stats = coordinator->GetComponent<Statistics>(*enemy);
		auto& p_sprite = coordinator->GetComponent<Sprite>(*player);
		auto& e_sprite = coordinator->GetComponent<Sprite>(*enemy);
		
		sf::RectangleShape background;
		sf::Texture background_texture;
		background.setSize(sf::Vector2f(window->getSize()));

		if (!background_texture.loadFromFile("Resources/Images/Backgrounds/pixel_forest.png"))
		{
			throw"ERROR::MAIN_MENU_STATE::FAIL_TO_LOAD_BACKGROUND_TEXTURE";
		}

		background.setTexture(&background_texture);
		
		while(p_stats.health>0)
		{
			if (rand() % 100 > 10)
				p_stats.health--;
		}
	}

};