#pragma once

#include "../Components.hpp"
#include "../Core/Coordinator.hpp"

class CollisionSystem
	:public System
{
public:

	void init(Coordinator* coordinator)
	{
		for (auto const& entity : mEntities)
		{

			auto& collider = coordinator->GetComponent<Collider>(entity);
			auto& transform = coordinator->GetComponent<Transform>(entity);

			collider.hitbox = sf::FloatRect(transform.position.x, transform.position.y, collider.widht, collider.hight);
			
			collider.colliding["UP"] = false;
			collider.colliding["DOWN"] = false;
			collider.colliding["LEFT"] = false;
			collider.colliding["RIGHT"] = false;
		}
	}

	void update(Coordinator* coordinator)
	{
		for (auto const& entity : mEntities)
		{
			auto& transform = coordinator->GetComponent<Transform>(entity);
			auto& collider = coordinator->GetComponent<Collider>(entity);
			collider.hitbox = sf::FloatRect(transform.position.x, transform.position.y, collider.widht, collider.hight);
		}
	}

	void collide(Coordinator* coordinator, Entity* player)
	{
		bool haveColliderTop = false;
		bool haveColliderBottom = false;
		bool haveColliderLeft = false;
		bool haveColliderRight = false;
		auto& p_collider = coordinator->GetComponent<Collider>(*player);
		auto& p_physical = coordinator->GetComponent<Physical>(*player);
		p_collider.hitbox = sf::FloatRect(p_physical.move_predict.x, p_physical.move_predict.y, p_collider.widht, p_collider.hight);

		
		for (auto const& entity : mEntities)
		{
			auto& collider = coordinator->GetComponent<Collider>(entity);
			if (p_collider.flag != collider.flag)
			{
				//if(p_collider.hitbox.intersects(collider.hitbox))
				//{
				//	std::cout << "Collision" << std::endl;
				//	haveColliderTop = true;
				//}
				if((p_collider.hitbox.top-1 <= collider.hitbox.top+collider.hitbox.height) && (p_collider.hitbox.top > collider.hitbox.top)
					&& (((p_collider.hitbox.left >= collider.hitbox.left) && (p_collider.hitbox.left <= collider.hitbox.left + collider.hitbox.width))
					|| ((p_collider.hitbox.left + p_collider.hitbox.width >= collider.hitbox.left) && (p_collider.hitbox.left + p_collider.hitbox.width <= collider.hitbox.left + collider.hitbox.width))))
				{
					std::cout << "Collision Top" << std::endl;
					haveColliderTop = true;
				}
				if ((p_collider.hitbox.top + p_collider.hitbox.height + 1 >= collider.hitbox.top) && (p_collider.hitbox.top + p_collider.hitbox.height < collider.hitbox.top + collider.hitbox.height)
					&& (((p_collider.hitbox.left >= collider.hitbox.left) && (p_collider.hitbox.left <= collider.hitbox.left + collider.hitbox.width))
					|| ((p_collider.hitbox.left + p_collider.hitbox.width >= collider.hitbox.left) && (p_collider.hitbox.left + p_collider.hitbox.width <= collider.hitbox.left + collider.hitbox.width))))
				{
					std::cout << "Collision Bottom" << std::endl;
					haveColliderBottom = true;
				}
				if ((p_collider.hitbox.left -1 <= collider.hitbox.left+collider.hitbox.width) && (p_collider.hitbox.left > collider.hitbox.left)
					&& (((p_collider.hitbox.top>=collider.hitbox.top) && (p_collider.hitbox.top<=collider.hitbox.top+collider.hitbox.height))
					|| ((p_collider.hitbox.top + p_collider.hitbox.height >= collider.hitbox.top) && (p_collider.hitbox.top + p_collider.hitbox.height <= collider.hitbox.top + collider.hitbox.height))))
				{
					std::cout << "Collision Left" << std::endl;
					haveColliderLeft = true;
				}
				if ((p_collider.hitbox.left +p_collider.hitbox.width + 1 >= collider.hitbox.left) && (p_collider.hitbox.left + p_collider.hitbox.width < collider.hitbox.left + collider.hitbox.width)
					&& (((p_collider.hitbox.top >= collider.hitbox.top) && (p_collider.hitbox.top <= collider.hitbox.top + collider.hitbox.height))
					|| ((p_collider.hitbox.top + p_collider.hitbox.height >= collider.hitbox.top) && (p_collider.hitbox.top + p_collider.hitbox.height <= collider.hitbox.top + collider.hitbox.height))))
				{
					std::cout << "Collision Right" << std::endl;
					haveColliderRight = true;
				}
			}
			
		}

		p_collider.colliding.at("UP") = haveColliderTop;
		p_collider.colliding.at("DOWN") = haveColliderBottom;
		p_collider.colliding.at("LEFT") = haveColliderLeft;
		p_collider.colliding.at("RIGHT") = haveColliderRight;
	}

	void render(Coordinator* coordinator, sf::RenderWindow* window)
	{
		for (auto const& entity : mEntities)
		{

			auto& collider = coordinator->GetComponent<Collider>(entity);
			sf::RectangleShape collision_box;
			collision_box.setPosition(sf::Vector2f(collider.hitbox.left, collider.hitbox.top));
			collision_box.setSize(sf::Vector2f(collider.widht, collider.hight));
			collision_box.setFillColor(sf::Color::Red);
			window->draw(collision_box);
		}
			
	}
};