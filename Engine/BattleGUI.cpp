#include "BattleGUI.hpp"


StatisticGUI::StatisticGUI(Coordinator* coordinator,Entity* entity, sf::Font* font)
{
	shape.setSize(sf::Vector2f(50,50));
	shape.setFillColor(sf::Color(30, 30, 200, 230));
	shape.setOutlineColor(sf::Color(200, 30, 200, 255));
	shape.setOutlineThickness(1);

	auto& e_stats = coordinator->GetComponent<Statistics>(*entity);
	auto& e_sprite = coordinator->GetComponent<Sprite>(*entity);

	shape.setPosition(e_sprite.sprite_rect.left+50, e_sprite.sprite_rect.top);

	sf::FloatRect shape_rect = shape.getGlobalBounds();
	
	name = sf::Text(e_stats.name, *font, 12);
	race = sf::Text(e_stats.race, *font, 10);
	level = sf::Text(std::to_string(e_stats.level), *font, 15);
	strenght = sf::Text("Str: " + std::to_string(e_stats.strenght),*font, 12);
	luck = sf::Text("Lck: " + std::to_string(e_stats.luck), *font, 12);
	magic = sf::Text("Mag: " + std::to_string(e_stats.magic), *font, 12);
	defense = sf::Text("Def: " + std::to_string(e_stats.defense), *font, 12);
	resistance = sf::Text("Res: " + std::to_string(e_stats.resistance), *font, 12);

	name.setPosition(shape_rect.left + shape_rect.width / 2 - name.getGlobalBounds().width / 2, shape_rect.top + 5);
	race.setPosition(shape_rect.left + shape_rect.width / 2 - name.getGlobalBounds().width / 2, shape_rect.top + 10);
	strenght.setPosition(shape_rect.left + shape_rect.width / 3 - name.getGlobalBounds().width / 2, shape_rect.top + 15);
	magic.setPosition(shape_rect.left + 2*shape_rect.width / 3 - name.getGlobalBounds().width / 2, shape_rect.top + 15);
	defense.setPosition(shape_rect.left + 2*shape_rect.width / 3 - name.getGlobalBounds().width / 2, shape_rect.top + 20);
	resistance.setPosition(shape_rect.left + shape_rect.width / 3 - name.getGlobalBounds().width / 2, shape_rect.top + 20);
	luck.setPosition(shape_rect.left + shape_rect.width / 2 - name.getGlobalBounds().width / 2, shape_rect.top + 25);
	level.setPosition(shape_rect.left + shape_rect.width / 2 - name.getGlobalBounds().width / 2, shape_rect.top + 30);

	level.setFillColor(sf::Color::Red);
	
	exp_bar = new Bar(sf::Color(40, 40, 255, 255), sf::Color(0, 0, 0, 0), sf::Vector2f(30, 5), shape_rect,
	                  sf::Vector2f(0, -10), e_stats.max_expierence, e_stats.expirence, false);

	isActive = true;
}


void StatisticGUI::update(sf::Vector2f mousePos)
{
	//if (shape.getGlobalBounds().contains(mousePos))
	//	isActive = true;
	//else
	//	isActive = false;
}

void StatisticGUI::render(sf::RenderWindow* window)
{
	if (isActive)
	{
		window->draw(shape);
		window->draw(name);
		window->draw(race);
		window->draw(strenght);
		window->draw(magic);
		window->draw(defense);
		window->draw(resistance);
		window->draw(luck);
		window->draw(level);
		exp_bar->render(window);
	}
}

BattleGUI::BattleGUI(Coordinator* coordinator, sf::RenderWindow* window, sf::Font* f,sf::Texture& background_tex, std::list<Entity*> entites)
	: font(f), texture_background(background_tex),heroes_list(entites)
{
	background.setTexture(&texture_background);

	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y * 0.3));
	background.setPosition(sf::Vector2f(0, window->getSize().y * 0.7));

	for(auto& e:entites)
	{
		heroes_stats.emplace_back(StatisticGUI(coordinator, e, font));
	}
	
}

void BattleGUI::update(sf::Vector2f mousePos)
{
	for(auto& s:heroes_stats)
	{
		s.update(mousePos);
	}
}

void BattleGUI::render(sf::RenderWindow* window)
{
	for(auto& s:heroes_stats)
	{
		s.render(window);
	}
}
