#pragma once

#include "../Components.hpp"
#include "../Core/Coordinator.hpp"

class PhysicsSystem
	:public System
{
public:
	void update(float dt, Coordinator* coordinator)
	{
		for (auto const& entity : mEntities)
		{
			auto& transform = coordinator->GetComponent<Transform>(entity);
			auto& physical = coordinator->GetComponent<Physical>(entity);
			
			/*Decelerates the sprite and controls the velocity + move sprite*/
			if (physical.velocity.x > 0.f) //Check for positive x
			{
				//Max velocity check
				if (physical.velocity.x > physical.maxVelocity)
					physical.velocity.x = physical.maxVelocity;

				//Deceleration x positive
				physical.velocity.x -= physical.deceleration;
				if (physical.velocity.x < 0.f)
					physical.velocity.x = 0.f;
			}
			else if (physical.velocity.x < 0.f) //Check for negative x
			{
				//Max velocity check
				if (physical.velocity.x < -physical.maxVelocity)
					physical.velocity.x = -physical.maxVelocity;

				//Deceleration
				physical.velocity.x += physical.deceleration;
				if (physical.velocity.x > 0.f)
					physical.velocity.x = 0.f;
			}

			if (physical.velocity.y > 0.f) //Check for positive y
			{
				//Max velocity check
				if (physical.velocity.y > physical.maxVelocity)
					physical.velocity.y = physical.maxVelocity;

				//Deceleration
				physical.velocity.y -= physical.deceleration;
				if (physical.velocity.y < 0.f)
					physical.velocity.y = 0.f;
			}
			else if (physical.velocity.y < 0.f) //Check for negative y
			{
				//Max velocity check
				if (physical.velocity.y < -physical.maxVelocity)
					physical.velocity.y = -physical.maxVelocity;

				//Deceleration
				physical.velocity.y += physical.deceleration;
				if (physical.velocity.y > 0.f)
					physical.velocity.y = 0.f;
			}

			if (!physical.isIdle)
			{
				physical.velocity.x += physical.acceleration * physical.direction.x;

				physical.velocity.y += physical.acceleration * physical.direction.y;
			}

			transform.position += physical.velocity * dt;
			
		}
	}
};
