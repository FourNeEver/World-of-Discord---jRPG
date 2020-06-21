#pragma once
#include "Libraries.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Components.hpp"
#include "Button.hpp"
#include "Bar.hpp"
class StatisticGUI
{
	sf::RectangleShape shape;
	sf::FloatRect origin;
	
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
	sf::Text current_attacker;
	std::map<int, sf::ConvexShape> target_pointer;
	sf::ConvexShape action_pointer;
	
	std::list<Entity*> heroes_list;
	std::vector<StatisticGUI> heroes_stats;
	std::map<int, Entity>* all_heroes;
	Entity* enemy;



public:

	Button* attack;
	Button* ability;
	Button* item;
	Button* limit;
	std::map<int, Button*> enemy_ptr;

	bool isAttacking = false;

	
	
	BattleGUI(Coordinator* coordinator,sf::RenderWindow* window, sf::Font* f,sf::Texture& background_tex, std::list<Entity*> entites, std::map<int, Entity>* heroes, Entity* ene);
	
	void update(sf::Vector2f mousePos, std::string current_name, sf::FloatRect origin,std::string flag);
	void render(sf::RenderWindow* window);

	void kill(int ID);
};

