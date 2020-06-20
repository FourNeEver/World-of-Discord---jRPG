#pragma once
#include "Libraries.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Components.hpp"
#include "Button.hpp"
#include "Bar.hpp"
class StatisticGUI
{
	sf::RectangleShape shape;
	
	sf::Text name;
	sf::Text race;
	sf::Text level;
	sf::Text strenght;
	sf::Text luck;
	sf::Text magic;
	sf::Text defense;
	sf::Text resistance;
	
	Bar* exp_bar;

	bool isActive;
public:
	StatisticGUI(Coordinator* coordinator,Entity* entity,sf::Font* font);

	void update(sf::Vector2f mousePos);
	void render(sf::RenderWindow* window);
};



class BattleGUI
{
	sf::Font* font;
	sf::RectangleShape background;
	sf::Texture texture_background;
	std::list<Entity*> heroes_list;
	std::vector<StatisticGUI> heroes_stats;



public:
	BattleGUI(Coordinator* coordinator,sf::RenderWindow* window, sf::Font* f,sf::Texture& background_tex, std::list<Entity*> entites);
	
	void update(sf::Vector2f mousePos);
	void render(sf::RenderWindow* window);
};

