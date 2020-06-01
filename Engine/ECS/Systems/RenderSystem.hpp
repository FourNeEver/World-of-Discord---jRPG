#pragma once
#include "../Components.hpp"
#include "../Core/Coordinator.hpp"


class RenderSystem
	:public System
{
public:

	void init(Coordinator* coordinator)
	{
		for (auto const& entity : mEntities)
		{
			{
				auto& sprite = coordinator->GetComponent<Sprite>(entity);

				sprite.sprite.setTexture(sprite.texture);
				sprite.sprite.setTextureRect(sprite.sprite_rect);
			}
		}
	}
	
	void update(Coordinator* coordinator)
	{
		for (auto const& entity : mEntities)
		{
			{
				auto& sprite = coordinator->GetComponent<Sprite>(entity);
				auto& transform = coordinator->GetComponent<Transform>(entity);
				
				sprite.sprite.setPosition(transform.position);
				sprite.sprite.setScale(transform.scale);
				sprite.sprite.setRotation(transform.rotation);
			}
		}
	}

	void render(Coordinator* coordinator, sf::RenderWindow* window)
	{
		for (auto const& entity : mEntities)
		{
			{
				auto& sprite = coordinator->GetComponent<Sprite>(entity);

				
				
				window->draw(sprite.sprite);

			}
		}
	}
	
};




