#pragma once
#include "../Components.hpp"
#include "../Core/Coordinator.hpp"


class RenderSystem
	:public System
{
public:
	
	void update(Coordinator* coordinator)
	{
		for (auto const& entity : mEntities)
		{
			{
				auto& display = coordinator->GetComponent<Display>(entity);
				auto& transform = coordinator->GetComponent<Transform>(entity);

				display.sprite.setPosition(transform.position);
				display.sprite.setScale(transform.scale);
				display.sprite.setRotation(transform.rotation);
			}
		}
	}

	void render(Coordinator* coordinator, sf::RenderWindow* window)
	{
		for (auto const& entity : mEntities)
		{
			{
				auto& display = coordinator->GetComponent<Display>(entity);

				window->clear();
				
				window->draw(display.sprite);

			}
		}
	}
	
};




