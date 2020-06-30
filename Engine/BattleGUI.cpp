#include "BattleGUI.hpp"


StatisticGUI::StatisticGUI(Coordinator* coordinator,Entity* entity, sf::Font* font)
{
	shape.setSize(sf::Vector2f(100,100));
	shape.setFillColor(sf::Color(30, 30, 200, 230));
	shape.setOutlineColor(sf::Color(200, 30, 200, 255));
	shape.setOutlineThickness(1);

	auto& e_stats = coordinator->GetComponent<Statistics>(*entity);
	auto& e_sprite = coordinator->GetComponent<Sprite>(*entity);

	origin = e_sprite.sprite.getGlobalBounds();
	
	shape.setPosition(origin.left+50, origin.top-origin.height);

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
	race.setPosition(shape_rect.left + shape_rect.width / 2 - race.getGlobalBounds().width / 2, shape_rect.top + 15);
	strenght.setPosition(shape_rect.left + shape_rect.width / 4 - strenght.getGlobalBounds().width / 2, shape_rect.top + 25);
	magic.setPosition(shape_rect.left + 3*shape_rect.width / 4 - magic.getGlobalBounds().width / 2, shape_rect.top + 25);
	defense.setPosition(shape_rect.left + 3*shape_rect.width / 4 - defense.getGlobalBounds().width / 2, shape_rect.top + 35);
	resistance.setPosition(shape_rect.left + shape_rect.width / 4 - resistance.getGlobalBounds().width / 2, shape_rect.top + 35);
	luck.setPosition(shape_rect.left + shape_rect.width / 2 - luck.getGlobalBounds().width / 2, shape_rect.top + 45);
	level.setPosition(shape_rect.left + shape_rect.width / 2 - level.getGlobalBounds().width / 2, shape_rect.top + 65);

	level.setFillColor(sf::Color::Red);
	
	exp_bar = new Bar(sf::Color(40, 40, 255, 255), sf::Color(0, 0, 0, 0), sf::Vector2f(80, 5), shape_rect,
	                  sf::Vector2f(0, -10), e_stats.max_expierence, e_stats.expirence, false);

	isActive = true;
}


void StatisticGUI::update(sf::Vector2f mousePos)
{
	if (origin.contains(mousePos))
		isActive = true;
	else
		isActive = false;
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

BattleGUI::BattleGUI(Coordinator* coordinator, sf::RenderWindow* window, sf::Font* f,sf::Texture& background_tex, std::list<Entity*> entites, std::map<int, Entity>* heroes, Entity* ene, Entity* playr,std::map<int, Ability>* all_abs)
	: font(f), texture_background(background_tex),heroes_list(entites),all_heroes(heroes),all_abilities(all_abs),enemy(ene),player(playr)
{
	background.setTexture(&texture_background);

	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y * 0.3));
	background.setPosition(sf::Vector2f(0, window->getSize().y * 0.7));

	for(auto& e:entites)
	{
		heroes_stats.emplace_back(StatisticGUI(coordinator, e, font));
	}

	attack = new Button(825, 550, 175, 60, font, "Attack",
		15,
		sf::Color(255, 0, 0, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 0),
		sf::Color(255, 255, 255, 150),
		sf::Color(255, 255, 255, 255));
	
	ability = new Button(1050, 550, 175, 60, font, "Abilities",
		15,
		sf::Color(255, 0, 0, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 0),
		sf::Color(255, 255, 255, 150),
		sf::Color(255, 255, 255, 255));
	
	item = new Button(825, 625, 175, 60, font, "Items",
		15,
		sf::Color(255, 0, 0, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 0),
		sf::Color(255, 255, 255, 150),
		sf::Color(255, 255, 255, 255));
	
	limit = new Button(1050, 625, 175, 60, font, "Limit",
		15,
		sf::Color(255, 0, 0, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 0),
		sf::Color(255, 255, 255, 150),
		sf::Color(255, 255, 255, 255));
	
	enemy_ptr.try_emplace(0, new Button(300, 550, 175, 60, font, coordinator->GetComponent<Statistics>(*enemy).name,
		15,
		sf::Color(255, 0, 0, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 0),
		sf::Color(255, 255, 255, 150),
		sf::Color(255, 255, 255, 255)));

	float x = 1;
	float y = 0;
	for(auto& e :coordinator->GetComponent<Team>(*enemy).team)
	{
		if (x > 1)
		{
			x -= 2;
			y++;
		}
		enemy_ptr.try_emplace(e, new Button(300.f+(200.f*x), 550.f+(75.f*y), 175, 60, font, coordinator->GetComponent<Statistics>(all_heroes->at(e)).name,
			15,
			sf::Color(255, 0, 0, 255),
			sf::Color(255, 255, 255, 255),
			sf::Color(255, 255, 255, 255),
			sf::Color(255, 255, 255, 0),
			sf::Color(255, 255, 255, 150),
			sf::Color(255, 255, 255, 255)));
		x++;
	}

	ally_ptr.try_emplace(0, new Button(300, 550, 175, 60, font, coordinator->GetComponent<Statistics>(*player).name,
		15,
		sf::Color(255, 0, 0, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 0),
		sf::Color(255, 255, 255, 150),
		sf::Color(255, 255, 255, 255)));

	x = 1;
	y = 0;
	for (auto& e : coordinator->GetComponent<Team>(*player).team)
	{
		if (x > 1)
		{
			x -= 2;
			y++;
		}
		ally_ptr.try_emplace(e, new Button(300.f + (200.f * x), 550.f + (75.f * y), 175, 60, font, coordinator->GetComponent<Statistics>(all_heroes->at(e)).name,
			15,
			sf::Color(255, 0, 0, 255),
			sf::Color(255, 255, 255, 255),
			sf::Color(255, 255, 255, 255),
			sf::Color(255, 255, 255, 0),
			sf::Color(255, 255, 255, 150),
			sf::Color(255, 255, 255, 255)));
		x++;
	}
	
	for(unsigned int i=0;i<4;i++)
	{
		x = i;
		y = 0;
		if(x>1)
		{
			x -= 2;
			y++;
		}
		ability_ptr.emplace_back(new Button(300.f + (200.f * x), 550.f + (75.f*y), 175, 60, font, "ERROR::MISSING_ABILITY_INFO",
			15,
			sf::Color(255, 0, 0, 255),
			sf::Color(255, 255, 255, 255),
			sf::Color(255, 255, 255, 255),
			sf::Color(255, 255, 255, 0),
			sf::Color(255, 255, 255, 150),
			sf::Color(255, 255, 255, 255)));
	}
	
	current_attacker = sf::Text("Missing name", *font, 20);
	current_attacker.setPosition(sf::Vector2f(window->getSize().x / 2,525));
	current_attacker.setFillColor(sf::Color::Black);

	sf::FloatRect origin = coordinator->GetComponent<Sprite>(*enemy).sprite.getGlobalBounds();
	target_pointer.try_emplace(0, sf::ConvexShape(3));
	target_pointer.at(0).setPoint(0, sf::Vector2f(0.0, 0.0));
	target_pointer.at(0).setPoint(1, sf::Vector2f(15.0, 15.0));
	target_pointer.at(0).setPoint(2, sf::Vector2f(-15.0, 15.0));
	target_pointer.at(0).setFillColor(sf::Color::Red);
	target_pointer.at(0).setPosition(sf::Vector2f(origin.left + origin.width / 2, origin.top + origin.height + 2));
	
	for (auto& e : coordinator->GetComponent<Team>(*enemy).team)
	{
		origin = coordinator->GetComponent<Sprite>(all_heroes->at(e)).sprite.getGlobalBounds();
		target_pointer.try_emplace(e, sf::ConvexShape(3));
		target_pointer.at(e).setPoint(0, sf::Vector2f(0.0, 0.0));
		target_pointer.at(e).setPoint(1, sf::Vector2f(15.0, 15.0));
		target_pointer.at(e).setPoint(2, sf::Vector2f(-15.0, 15.0));
		target_pointer.at(e).setFillColor(sf::Color::Red);
		target_pointer.at(e).setPosition(sf::Vector2f(origin.left + origin.width /2,origin.top + origin.height + 2));
	}

	origin = coordinator->GetComponent<Sprite>(*heroes_list.front()).sprite.getGlobalBounds();
	action_pointer = sf::ConvexShape(3);
	action_pointer.setPoint(0, sf::Vector2f(0.0, 0.0));
	action_pointer.setPoint(1, sf::Vector2f(15.0, 15.0));
	action_pointer.setPoint(2, sf::Vector2f(-15.0, 15.0));
	action_pointer.setRotation(180);
	action_pointer.setFillColor(sf::Color::Green);
	action_pointer.setPosition(sf::Vector2f(origin.left + origin.width / 2, origin.top - 2));

}

void BattleGUI::update(sf::Vector2f mousePos, std::string current_name, sf::FloatRect origin, std::string flag, std::vector<int> abilities_IDs)
{

	current_attacker.setString(current_name);

	action_pointer.setPosition(sf::Vector2f(origin.left + origin.width / 2, origin.top - 2));

	
	for(auto& s:heroes_stats)
	{
		s.update(mousePos);
	}
	if(flag == "ENEMY")
	{
		attack->deactivate();
		ability->deactivate();
		item->deactivate();
		limit->deactivate();
	}
	else
	{
		attack->activate();
		ability->activate();
		item->activate();
		limit->activate();
	}
	attack->update(mousePos);
	ability->update(mousePos);
	item->update(mousePos);
	limit->update(mousePos);

	if (!abilities_IDs.empty())
	{
		for (unsigned int i = 0; i < abilities_IDs.size(); i++)
		{
			ability_ptr.at(i)->update(mousePos);

			if (ability->isPressed())
			{
				choosingAbility = true;

				ability_ptr.at(i)->activate();
				ability_ptr.at(i)->change(all_abilities->at(abilities_IDs.at(i)).name);
			}
			if (ability_ptr.at(i)->isPressed() && choosingAbility)
			{
				usingAbility = true;
				choosingAbility = false;

				target = all_abilities->at(abilities_IDs.at(i)).target;

				if (target == "ENEMY")
				{
					for (auto& e : enemy_ptr)
					{
						e.second->activate();
					}
				}
			}
			
		}
		
	}

	
	for (auto& e : ally_ptr)
	{
		e.second->update(mousePos);
		if (usingAbility && target == "ALLY")
		{
			e.second->activate();
			if (e.second->isPressed())
			{
				usingAbility = false;
				e.second->deactivate();
			}
		}
	}
	
	for (auto& e : enemy_ptr)
	{
		e.second->update(mousePos);
		if (attack->isPressed() )
		{
			isAttacking = true;

			e.second->activate();

		}
		if (isAttacking)
		{
			if (e.second->isPressed())
			{
				isAttacking = false;
				e.second->deactivate();
			}
		}
		if (usingAbility && target == "ENEMY")
		{
			if (e.second->isPressed())
			{
				usingAbility = false;
				e.second->deactivate();
			}
		}

		if(!isAttacking && !usingAbility)
		{
			e.second->deactivate();
		}
	}
}

void BattleGUI::render(sf::RenderWindow* window)
{
	for(auto& s:heroes_stats)
	{
		s.render(window);
	}
	attack->render(window);
	ability->render(window);
	item->render(window);
	limit->render(window);
	window->draw(current_attacker);
	window->draw(action_pointer);
	if(choosingAbility)
	{
		for(auto& b:ability_ptr)
		{
			b->render(window);
		}
	}
	if(isAttacking)
	{
		for(auto& e:enemy_ptr)
		{
			e.second->render(window);
			if(e.second->isHovered())
			{
				window->draw(target_pointer.at(e.first));
			}
		}
	}
	if(usingAbility)
	{
		if(target=="ENEMY")
		{
			for (auto& e : enemy_ptr)
			{
				e.second->render(window);
				if (e.second->isHovered())
				{
					window->draw(target_pointer.at(e.first));
				}
			}
		}
		if(target=="ALLY")
		{
			for (auto& e : ally_ptr)
			{
				e.second->render(window);
			}
		}
		if(target=="SELF")
		{
			ally_ptr.at(0)->render(window);
		}
	}
}
