#pragma once

#include "../Components.hpp"
#include "../Core/Coordinator.hpp"

class ControlSystem
	:public System
{
public:
	void update(Coordinator* coordinator, std::map<std::string, int>* keybinds)
	{
		for (auto const& entity : mEntities)
		{
			{
				auto& physical = coordinator->GetComponent<Physical>(entity);
				auto& animation = coordinator->GetComponent<Animated>(entity);

				physical.isIdle = true;
				physical.direction = sf::Vector2f(0, 0);
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_LEFT"))))
				{
					physical.direction.x = -1.f;
					physical.isIdle = false;
					animation.currentAnimation = "WALK_LEFT";
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_RIGHT"))))
				{
					physical.direction.x = 1.f;
					physical.isIdle = false;
					animation.currentAnimation = "WALK_RIGHT";
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_UP"))))
				{
					physical.direction.y = -1.f;
					physical.isIdle = false;
					animation.currentAnimation = "WALK_UP";
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds->at("MOVE_DOWN"))))
				{
					physical.direction.y = 1.f;
					physical.isIdle = false;
					animation.currentAnimation = "WALK_DOWN";
				}
				if(physical.isIdle)
					animation.currentAnimation = "IDLE";
			}
		}
	}

};