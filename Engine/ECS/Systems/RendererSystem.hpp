#pragma once
#include "../Components.hpp"
#include "../Core/Coordinator.hpp"


class RendererSystem
	:public System
{
public:
	void update(float dt, Coordinator* coordinator)
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
	
};




