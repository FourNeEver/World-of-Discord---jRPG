#pragma once


#include "../Components.hpp"
#include "../Core/Coordinator.hpp"

class AnimationSystem
	:public System
{
public:

	void init(Coordinator* coordinator)
	{
		for (auto const& entity : mEntities)
		{
			auto& animated = coordinator->GetComponent<Animated>(entity);
			auto& sprite = coordinator->GetComponent<Sprite>(entity);

			std::ifstream ifs(animated.path);
			if (ifs.is_open())
			{
				std::string animationName;
				float animation_timer = 0;
				int start_frame_x = 0, start_frame_y = 0, frames_x = 0, frames_y = 0,
				width = 0, height = 0;

				while (ifs >> animationName >> animation_timer >> start_frame_x >> start_frame_y >> frames_x >> frames_y >> width >> height)
				{
					animated.animations[animationName] = new Animation(&sprite.sprite, &sprite.texture, animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height);
				}
				
			}
		}
	};

	void update(Coordinator* coordinator, const float& dt)
	{
		for (auto const& entity : mEntities)
		{
			auto& animated = coordinator->GetComponent<Animated>(entity);

			animated.animations[animated.currentAnimation]->play(dt);
		}
	}

	void reinit(Coordinator *coordinator)
	{
		for (auto const& entity : mEntities)
		{
			auto& animated = coordinator->GetComponent<Animated>(entity);

			animated.animations.clear();
		}

		init(coordinator);
	}
};