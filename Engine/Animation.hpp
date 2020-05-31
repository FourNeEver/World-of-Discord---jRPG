#pragma once

#include "Libraries.hpp"

class Animation
{
public:
	sf::Sprite* sprite;
	sf::Texture* textureSheet;
	float animationTimer;
	float timer;
	int width;
	int height;


	
	sf::IntRect startRect;
	sf::IntRect currentRect;
	sf::IntRect endRect;


	Animation(sf::Sprite* sprite, sf::Texture* textureSheet, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
		: sprite(sprite), textureSheet(textureSheet), animationTimer(animation_timer), width(width), height(height)
	{
		timer = 0.f;

		startRect = sf::IntRect(start_frame_x * width, start_frame_y * width, width, height);
		currentRect = startRect;
		endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

		this->sprite->setTexture(*textureSheet, true);
		this->sprite->setTextureRect(startRect);
	}

	//Functions
	void play(const float& dt)
	{
		timer += 1000.f * dt;
		if (timer >= animationTimer)
		{
			//reset timer
			timer = 0.f;

			//Animate
			if (currentRect.left != endRect.left)
			{
				currentRect.left += width;
			}
			else
			{
				currentRect.left = startRect.left;
			}

			sprite->setTextureRect(currentRect);

		}
	}

	void reset()
	{
		timer = 0.f;
		currentRect = startRect;
	}

};