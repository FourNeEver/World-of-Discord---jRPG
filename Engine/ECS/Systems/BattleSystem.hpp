#pragma once

//#include "../../Bar.hpp"
//#include "../../Button.hpp"
//#include "../Components.hpp"
//#include "../Core/Coordinator.hpp"
#include "../../BattleGUI.hpp"


class BattleSystem
	:public System
{
public:
	
	void compare_agility(Coordinator* coordinator, std::list<Entity*>& queue)
	{
		std::list<Entity*> temp_queue;
		int highest = 0;
		Entity* best;
		for (unsigned int i = queue.size(); i > 0; i--)
		{
			for (std::list<Entity*>::iterator it = queue.begin();it!=queue.end();++it)
			{
				int speed = coordinator->GetComponent<Statistics>(**it).luck;
				if (speed > highest)
				{
					highest = speed;
					best = *it;
					
				}

			}
			queue.remove(best);
			temp_queue.emplace_back(best);
			best = nullptr;
			highest = 0;
		}
		queue = temp_queue;
	}

	
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
	
	void update(Coordinator* coordinator, Entity* player, Entity* enemy, sf::RenderWindow* window,
		std::shared_ptr<RenderSystem> renderer, std::shared_ptr<AnimationSystem> animator, std::map<int, Entity>* heroes)
	{

		//for (auto const& entity : mEntities)
		//{
			//Player components
		auto& p_stats = coordinator->GetComponent<Statistics>(*player);
		auto& p_physics = coordinator->GetComponent<Physical>(*player);
		auto& p_animation = coordinator->GetComponent<Animated>(*player);
		auto& p_transform = coordinator->GetComponent<Transform>(*player);
		auto& p_sprite = coordinator->GetComponent<Sprite>(*player);
		auto& p_team = coordinator->GetComponent<Team>(*player);
		auto& p_GUI = coordinator->GetComponent<GUI>(*player);

		//Enemy components
		auto& e_transform = coordinator->GetComponent<Transform>(*enemy);
		auto& e_stats = coordinator->GetComponent<Statistics>(*enemy);
		auto& e_sprite = coordinator->GetComponent<Sprite>(*enemy);
		auto& e_collider = coordinator->GetComponent<Collider>(*enemy);
		auto& e_animation = coordinator->GetComponent<Animated>(*enemy);
		auto& e_team = coordinator->GetComponent<Team>(*enemy);
		auto& e_GUI = coordinator->GetComponent<GUI>(*enemy);

		p_animation.currentAnimation = "IDLE";

		if (e_collider.colliding.at("ACTION"))
		{
			//Time var
			sf::Clock DeltaTime;
			sf::Time Elapsed;
			sf::Time Timer;

			//Mouse position
			sf::Vector2f mousePosWiew;


			//Booleans
			bool fighting = true;
			bool action_avaible = true;

			//Queue management
			std::list<Entity*>::iterator current_hero;


			//Loading fonts
			sf::Font font;

			if (!font.loadFromFile("Resources/Fonts/arial.ttf"))
			{
				throw("ERROR::BATTLE::COULD NOT LOAD FONT");
			}

			///Loading backgrounds
			//Main background
			sf::RectangleShape background;
			sf::Texture background_texture;

			if (!background_texture.loadFromFile("Resources/Images/Backgrounds/pixel_forest.png"))
			{
				throw"ERROR::BATTLE::FAIL_TO_LOAD_BACKGROUND_TEXTURE";
			}

			background.setSize(sf::Vector2f(window->getSize()));
			background.setPosition(sf::Vector2f(0, -185));
			background.setTexture(&background_texture);

			//GUI Background
			sf::RectangleShape GUI_background(sf::Vector2f(window->getSize().x, 200));
			sf::Texture GUI_texture;
			if (!GUI_texture.loadFromFile("Resources/Images/Backgrounds/action_gui.jpg"))
			{
				throw"ERROR::BATTLE::FAIL_TO_LOAD_BACKGROUND_TEXTURE";
			}
			GUI_background.setTexture(&GUI_texture);
			GUI_background.setPosition(sf::Vector2f(0, window->getSize().y - GUI_background.getSize().y));
			//GUI_background.setFillColor(sf::Color(140,140,60,255));
			GUI_background.setOutlineColor(sf::Color::Black);
			GUI_background.setOutlineThickness(1);

			
			//Setting up buttons
			//Button attack_btn(1000, 650, 100, 50, &font, "Attack",
			//	15,
			//	sf::Color(255, 0, 0, 255),
			//	sf::Color(255, 255, 255, 255),
			//	sf::Color(255, 255, 255, 255),
			//	sf::Color(255, 255, 255, 0),
			//	sf::Color(255, 255, 255, 150),
			//	sf::Color(255, 255, 255, 255));

			//Saving previous position
			auto p_transform_copy = coordinator->GetComponent<Transform>(*player);
			auto e_transform_copy = coordinator->GetComponent<Transform>(*enemy);

			//Player team init
			p_animation.currentAnimation = "IDLE_SIDE";
			p_transform.position = sf::Vector2f(1100, 450);
			int place = 1;

			for (auto& t : p_team.team)
			{
				coordinator->GetComponent<Sprite>(heroes->at(t)).isVisible = true;
				if (!(place % 2))
					coordinator->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(p_transform.position.x, p_transform.position.y - (50 * place));
				else
					coordinator->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(p_transform.position.x - 70, p_transform.position.y - (50 * place));
				std::cout << coordinator->GetComponent<Statistics>(heroes->at(t)).name << std::endl;
				place++;
			}

			//Enemy team init
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
				coordinator->GetComponent<Statistics>(heroes->at(t)).flag = "ENEMY";
				std::cout << coordinator->GetComponent<Statistics>(heroes->at(t)).name << std::endl;
				place++;
			}

			//Renderer update
			renderer->update(coordinator);


			//GUI update
			p_GUI.health_bar.update_origin(p_sprite.sprite.getGlobalBounds());
			e_GUI.health_bar.update_origin(e_sprite.sprite.getGlobalBounds());

			for (auto& t : p_team.team)
			{
				coordinator->GetComponent<GUI>(heroes->at(t)).health_bar.update_origin(coordinator->GetComponent<Sprite>(heroes->at(t)).sprite.getGlobalBounds());
			}

			for (auto& t : e_team.team)
			{
				coordinator->GetComponent<GUI>(heroes->at(t)).health_bar.update_origin(coordinator->GetComponent<Sprite>(heroes->at(t)).sprite.getGlobalBounds());
			}
			
			std::list<Entity*> living;
			living.emplace_back(player);
			living.emplace_back(enemy);
			for (auto& t : p_team.team)
			{
				living.emplace_back(&heroes->at(t));
			}
			for (auto& t : e_team.team)
			{
				living.emplace_back(&heroes->at(t));
			}

			//Fight loop
			while (fighting)
			{
				//Queue set up
				std::list<Entity*> action_queue = living;
				
				compare_agility(coordinator, action_queue);


				BattleGUI battle_gui(coordinator, window, &font, background_texture, action_queue,heroes,enemy);

				//std::cout << "Battle order: " << std::endl;
				//for (auto& hero : action_queue)
				//{
				//	std::cout << coordinator->GetComponent<Statistics>(*hero).name << std::endl;;
				//}
				while (!action_queue.empty() && fighting)
				{
					//Timer reset
					Elapsed = DeltaTime.restart();
					
					//Mouse Position Update
					mousePosWiew = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
					//std::cout << mousePosWiew.x << " " << mousePosWiew.y << std::endl;

					//Input handling
					//Debug input
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
						fighting = false;
					
					
					//Pulling current hero stats;
					current_hero = action_queue.begin();

					auto& h_stats = coordinator->GetComponent<Statistics>(**current_hero);
					auto& h_sprite = coordinator->GetComponent<Sprite>(**current_hero);



					
					//Actions
					if (h_stats.flag=="ALLY")
					{
						if (battle_gui.enemy_ptr.at(0)->isPressed())
						{
							phys_attack(coordinator, h_stats, coordinator->GetComponent<Statistics>(*enemy));
							action_avaible = false;
							action_queue.pop_front();
						}
						for (auto& e : e_team.team)
						{
							if (battle_gui.enemy_ptr.at(e)->isPressed())
							{

								phys_attack(coordinator, h_stats, coordinator->GetComponent<Statistics>(heroes->at(e)));
								action_avaible = false;
								action_queue.pop_front();
							}
						}
					}
					if (h_stats.flag=="ENEMY")
					{
						Timer += DeltaTime.getElapsedTime();
						if (Timer.asMicroseconds() > 20000)
						{
							phys_attack(coordinator, h_stats, p_stats);
							action_avaible = true;
							Timer = sf::Time::Zero;
							action_queue.pop_front();
						}
					}


					//Killing heroes
					for (auto& l : living)
					{
						if (coordinator->GetComponent<Statistics>(*l).health <= 0)
						{
							living.remove(l);
							break;
						}
					}
					//Removing dead heroes from queue
					for (auto& a : action_queue)
					{
						if (coordinator->GetComponent<Statistics>(*a).health <= 0)
						{
							action_queue.remove(a);
							break;
						}
					}
					
					//Removing buttons
					//if (coordinator->GetComponent<Statistics>(*enemy).health <= 0)
					//	battle_gui.kill(0);
					//for (auto& e : e_team.team)
					//{
					//	if (coordinator->GetComponent<Statistics>(heroes->at(e)).health <= 0)
					//		battle_gui.kill(e);
					//}

					//Fight ending
					bool enemy_alive = false;
					if (e_stats.health > 0)
						enemy_alive = true;
					for (auto& e : e_team.team)
					{
						if (coordinator->GetComponent<Statistics>(heroes->at(e)).health > 0)
							enemy_alive = true;
					}
					if (!enemy_alive)
						fighting = false;


					///Systems update

					//Bars update
					for (auto& l : living)
					{
						coordinator->GetComponent<GUI>(*l).health_bar.update(coordinator->GetComponent<Statistics>(*l).health);
					}
					
					//GUI Update
					battle_gui.update(mousePosWiew,h_stats.name,h_sprite.sprite.getGlobalBounds(),h_stats.flag);
					
					//Coordinator system update

					animator->update(coordinator, Elapsed.asSeconds());
					renderer->update(coordinator);



					///Display
					//Preparations
					window->clear();

					//Background render
					window->draw(background);


					//Sprite render
					for(auto& l:living)
					{
						window->draw(coordinator->GetComponent<Sprite>(*l).sprite);
					}

					//Bars Render
					for (auto& l : living)
					{
						coordinator->GetComponent<GUI>(*l).health_bar.render(window);
					}	

					//GUI Render
					window->draw(GUI_background);

					battle_gui.render(window);
					
					//Display window
					window->display();

					//View set
					window->setView(sf::View(sf::FloatRect(0, 0, 1280, 720)));

					
				}

			}

			//Killing enemy
			e_collider.colliding.at("ACTION") = false;
			e_stats.alive = false;


			//Hiding team sprites
			for (auto& t : p_team.team)
			{
				coordinator->GetComponent<Sprite>(heroes->at(t)).isVisible = false;
			}
			for (auto& t : e_team.team)
			{
				coordinator->GetComponent<Sprite>(heroes->at(t)).isVisible = false;
			}

			//Revertiong positions
			p_transform = p_transform_copy;
			e_transform = e_transform_copy;

			//Stopping the player
			p_physics.velocity = sf::Vector2f(0, 0);
		}
		/*}*/
		
	}
};