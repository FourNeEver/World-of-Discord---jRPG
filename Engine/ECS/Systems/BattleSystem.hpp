#pragma once

#include "../Bar.hpp"
#include "../Button.hpp"
#include "../Components.hpp"
#include "../Core/Coordinator.hpp"


class BattleSystem
	:public System
{
public:
	
	void update(Coordinator* coordinator,Entity* player, sf::RenderWindow* window,
		std::shared_ptr<RenderSystem> renderer, std::shared_ptr<AnimationSystem> animator)
	{
		
		for (auto const& entity : mEntities)
		{
			//Player components
			auto& p_stats = coordinator->GetComponent<Statistics>(*player);
			auto& p_physics = coordinator->GetComponent<Physical>(*player);
			auto& p_animation = coordinator->GetComponent<Animated>(*player);
			auto& p_transform = coordinator->GetComponent<Transform>(*player);
			auto& p_sprite = coordinator->GetComponent<Sprite>(*player);

			//Enemy components
			auto& e_transform = coordinator->GetComponent<Transform>(entity);
			auto& e_stats = coordinator->GetComponent<Statistics>(entity);
			auto& e_sprite = coordinator->GetComponent<Sprite>(entity);
			auto& e_collider = coordinator->GetComponent<Collider>(entity);

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

				Bar player_health(sf::Color::Green, sf::Color::Red, sf::Vector2f(100, 5), sf::Vector2f(975, 475), p_stats.max_health, p_stats.health);
				Bar enemy_health(sf::Color::Green, sf::Color::Red, sf::Vector2f(100, 5), sf::Vector2f(175, 475), e_stats.max_health, e_stats.health);
				auto p_transform_copy = coordinator->GetComponent<Transform>(*player);
				auto e_transform_copy = coordinator->GetComponent<Transform>(entity);
				
				
				Button attack(1000,650,100,50,&font,"Attack",
					12,
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

				p_transform.position = sf::Vector2f(1000, 400);
				e_transform.position = sf::Vector2f(200, 400);
				
				while (fighting)
				{

					Elapsed = DeltaTime.restart();
					
					mousePosWiew = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
					std::cout << mousePosWiew.x << " " << mousePosWiew.y << std::endl;

					attack.update(mousePosWiew);
					
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
						fighting = false;
					
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						e_stats.health -= 1;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						e_stats.health += 1;
					
					if (e_stats.health <= 0)
						fighting = false;

					if(action_avaible)
						if (attack.isPressed())
						{
							e_stats.health -= 10;
							action_avaible = false;
						}
					if(!action_avaible)
					{
						Timer += DeltaTime.getElapsedTime();
						if (Timer.asSeconds() > 1)
						{
							p_stats.health -= (rand() % 12);
							action_avaible = true;
							Timer = sf::Time::Zero;
						}
					}
					
					//Systems update
					player_health.update(p_stats.health);
					enemy_health.update(e_stats.health);

					

					
					
					animator->update(coordinator, Elapsed.asSeconds());
					renderer->update(coordinator);

					

					//Display
					window->clear();
					window->draw(background);


					window->draw(p_sprite.sprite);
					window->draw(e_sprite.sprite);
					player_health.render(window);
					enemy_health.render(window);

					window->draw(GUI_background);
					
					attack.render(window);
					
					window->display();

					window->setView(sf::View(sf::FloatRect(0, 0, 1280, 720)));

					

				}
				e_collider.colliding.at("ACTION") = false;
				e_stats.alive = false;


				p_transform = p_transform_copy;
				e_transform = e_transform_copy;
				p_physics.velocity = sf::Vector2f(0, 0);
				//p_animation.animations[p_animation.currentAnimation]->reset();
			}
		}
		
	}
};