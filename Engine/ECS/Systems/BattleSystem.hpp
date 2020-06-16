#pragma once

#include "../Bar.hpp"
#include "../Button.hpp"
#include "../Components.hpp"
#include "../Core/Coordinator.hpp"


class BattleSystem
	:public System
{
public:

	void phys_attack(Coordinator* coordinator, Statistics& a_stats, Statistics& d_stats)
	{
		srand(time(NULL));
		
		int damage = 0;
		
		if(rand()%100 <= a_stats.luck)
		{
			damage = (rand() % 5 + (a_stats.strenght * 2) - (d_stats.defense / 2))*2;
			d_stats.health -= damage;
			std::cout << a_stats.name << " critical strikes " << d_stats.name << " for " << damage << " damage"<<std::endl;
		}
		else
		{
			damage = rand() % 5 + (a_stats.strenght * 2) - (d_stats.defense/2);
			d_stats.health -= damage;
			std::cout <<a_stats.name<< " attacks " <<d_stats.name<<" for "<< damage << " damage" << std::endl;
		}
	}
	
	void update(Coordinator* coordinator,Entity* player, sf::RenderWindow* window,
		std::shared_ptr<RenderSystem> renderer, std::shared_ptr<AnimationSystem> animator, std::map<int, Entity>* heroes)
	{
		
		for (auto const& entity : mEntities)
		{
			//Player components
			auto& p_stats = coordinator->GetComponent<Statistics>(*player);
			auto& p_physics = coordinator->GetComponent<Physical>(*player);
			auto& p_animation = coordinator->GetComponent<Animated>(*player);
			auto& p_transform = coordinator->GetComponent<Transform>(*player);
			auto& p_sprite = coordinator->GetComponent<Sprite>(*player);
			auto& p_team = coordinator->GetComponent<Team>(*player);

			//Enemy components
			auto& e_transform = coordinator->GetComponent<Transform>(entity);
			auto& e_stats = coordinator->GetComponent<Statistics>(entity);
			auto& e_sprite = coordinator->GetComponent<Sprite>(entity);
			auto& e_collider = coordinator->GetComponent<Collider>(entity);
			auto& e_animation = coordinator->GetComponent<Animated>(entity);
			auto& e_team = coordinator->GetComponent<Team>(entity);

			p_animation.currentAnimation = "IDLE";
			
			if (e_collider.colliding.at("ACTION"))
			{

				sf::Clock DeltaTime;
				sf::Time Elapsed;
				sf::Time Timer;
				
				sf::Vector2f mousePosWiew;
				
				sf::RectangleShape background;
				sf::Texture background_texture;
				sf::Font font;

				bool fighting = true;
				bool action_avaible = true;
				
				background.setSize(sf::Vector2f(window->getSize()));
				
				sf::RectangleShape GUI_background(sf::Vector2f(window->getSize().x, 200));
				GUI_background.setPosition(sf::Vector2f(0,window->getSize().y-GUI_background.getSize().y));
				GUI_background.setFillColor(sf::Color::Blue);
				GUI_background.setOutlineColor(sf::Color::Black);
				GUI_background.setOutlineThickness(1);

				background.setPosition(sf::Vector2f(0, -185));

				Button attack_btn(1000, 650, 100, 50, &font, "Attack",
					10,
					sf::Color(255, 0, 0, 255),
					sf::Color(255, 255, 255, 255),
					sf::Color(255, 255, 255, 255),
					sf::Color(255, 255, 255, 255),
					sf::Color(255, 0, 0, 255),
					sf::Color(255, 255, 255, 255));

				if (!font.loadFromFile("Resources/Fonts/arial.ttf"))
				{
					throw("ERROR::BATTLE::COULD NOT LOAD FONT");
				}

				if (!background_texture.loadFromFile("Resources/Images/Backgrounds/pixel_forest.png"))
				{
					throw"ERROR::BATTLE::FAIL_TO_LOAD_BACKGROUND_TEXTURE";
				}

				background.setTexture(&background_texture);
				

				auto p_transform_copy = coordinator->GetComponent<Transform>(*player);
				auto e_transform_copy = coordinator->GetComponent<Transform>(entity);

				p_animation.currentAnimation = "IDLE_SIDE";
				p_transform.position = sf::Vector2f(1100, 450);
				int place = 1;

				for (auto& t : p_team.team)
				{
					coordinator->GetComponent<Sprite>(heroes->at(t)).isVisible = true;
					if (!(place % 2))
						coordinator->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(p_transform.position.x, p_transform.position.y - (50 * place));
					else
						coordinator->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(p_transform.position.x-70, p_transform.position.y - (50 * place));
					std::cout << coordinator->GetComponent<Statistics>(heroes->at(t)).name << std::endl;
					place++;
				}

				e_animation.currentAnimation = "IDLE_SIDE";
				e_transform.position = sf::Vector2f(200, 400);

				place = 1;
				for (auto& t : e_team.team)
				{
					coordinator->GetComponent<Sprite>(heroes->at(t)).isVisible = true;
					if (!(place % 2))
						coordinator->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(e_transform.position.x, e_transform.position.y - (50 * place));
					else
						coordinator->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(e_transform.position.x - 70, e_transform.position.y - (50 * place));
					std::cout << coordinator->GetComponent<Statistics>(heroes->at(t)).name << std::endl;
					place++;
				}

				renderer->update(coordinator);
				
				Bar player_health(sf::Color::Green, sf::Color::Red, sf::Vector2f(5, 64), p_sprite.sprite.getGlobalBounds(),sf::Vector2f(10,0), p_stats.max_health, p_stats.health,true);
				Bar enemy_health(sf::Color::Green, sf::Color::Red, sf::Vector2f(5, 65), e_sprite.sprite.getGlobalBounds(), sf::Vector2f(-e_sprite.sprite.getGlobalBounds().width-5,0), e_stats.max_health, e_stats.health,true);

				std::vector<Bar*> p_team_health;
				std::vector<Bar*> e_team_health;
				
				for (auto& t : p_team.team)
				{
					auto& t_stats = coordinator->GetComponent<Statistics>(heroes->at(t));
					auto& t_sprite = coordinator->GetComponent<Sprite>(heroes->at(t));
					p_team_health.emplace_back(new Bar(sf::Color::Green, sf::Color::Red, sf::Vector2f(5, 64), t_sprite.sprite.getGlobalBounds(), sf::Vector2f(10, 0), t_stats.max_health, t_stats.health, true));
				}

				for (auto& t : e_team.team)
				{
					auto& t_stats = coordinator->GetComponent<Statistics>(heroes->at(t));
					auto& t_sprite = coordinator->GetComponent<Sprite>(heroes->at(t));
					e_team_health.emplace_back(new Bar(sf::Color::Green, sf::Color::Red, sf::Vector2f(5, 64), t_sprite.sprite.getGlobalBounds(), sf::Vector2f(-t_sprite.sprite.getGlobalBounds().width - 5, 0), t_stats.max_health, t_stats.health, true));
				}
				
				while (fighting)
				{

					Elapsed = DeltaTime.restart();
					
					mousePosWiew = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
					//std::cout << mousePosWiew.x << " " << mousePosWiew.y << std::endl;

					attack_btn.update(mousePosWiew);
					
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
						fighting = false;
					
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						e_stats.health -= 1;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						e_stats.health += 1;
					
					if (e_stats.health <= 0)
						fighting = false;

					if(action_avaible)
						if (attack_btn.isPressed())
						{
							phys_attack(coordinator, p_stats, e_stats);
							action_avaible = false;
						}
					if(!action_avaible)
					{
						Timer += DeltaTime.getElapsedTime();
						if (Timer.asMicroseconds() > 20000)
						{
							phys_attack(coordinator, e_stats, p_stats);
							action_avaible = true;
							Timer = sf::Time::Zero;
						}
					}
					
					//Systems update
					player_health.update(p_stats.health);
					enemy_health.update(e_stats.health);

					for (auto t : p_team_health)
					{
						t->update(20);
					}

					for (auto t : e_team_health)
					{
						t->update(20);
					}

					
					
					animator->update(coordinator, Elapsed.asSeconds());
					renderer->update(coordinator);

					

					//Display
					window->clear();
					window->draw(background);



					window->draw(p_sprite.sprite);
					window->draw(e_sprite.sprite);

					for (auto& t : p_team.team)
					{
						window->draw(coordinator->GetComponent<Sprite>(heroes->at(t)).sprite);
					}
					for (auto& t : e_team.team)
					{
						window->draw(coordinator->GetComponent<Sprite>(heroes->at(t)).sprite);
					}
					
					player_health.render(window);
					enemy_health.render(window);

					for(auto t:p_team_health)
					{
						t->render(window);
					}

					for (auto t : e_team_health)
					{
						t->render(window);
					}

					window->draw(GUI_background);
					
					attack_btn.render(window);
					
					window->display();

					window->setView(sf::View(sf::FloatRect(0, 0, 1280, 720)));

					

				}
				e_collider.colliding.at("ACTION") = false;
				e_stats.alive = false;

				for (auto& t : p_team.team)
				{
					coordinator->GetComponent<Sprite>(heroes->at(t)).isVisible = false;
				}
				for (auto& t : e_team.team)
				{
					coordinator->GetComponent<Sprite>(heroes->at(t)).isVisible = false;
				}

				p_transform = p_transform_copy;
				e_transform = e_transform_copy;
				p_physics.velocity = sf::Vector2f(0, 0);
			}
		}
		
	}
};