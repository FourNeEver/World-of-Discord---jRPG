#include "../../BattleGUI.hpp"


class BattleSystem
	:public System
{
public:
	void aggro_check(Coordinator* cardinal, Entity* enemy)
	{
		if(cardinal->GetComponent<Collider>(*enemy).colliding.at("ACTION"))
		{
			cardinal->GetComponent<Combat>(*enemy).in_combat = true;
		}
		else
		{
			cardinal->GetComponent<Combat>(*enemy).in_combat = false;
		}
	}

	void compare_agility(Coordinator* coordinator, std::list<Entity*>& queue)
	{
		std::list<Entity*> temp_queue;
		int highest = 0;
		Entity* best;
		for (unsigned int i = queue.size(); i > 0; i--)
		{
			for (std::list<Entity*>::iterator it = queue.begin(); it != queue.end(); ++it)
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

	void phys_attack(Statistics& a_stats, Statistics& d_stats)
	{
		srand(time(NULL));

		int damage = 0;

		if (rand() % 100 <= a_stats.luck)
		{
			damage = (rand() % 5 + (a_stats.strenght * 2) - (d_stats.defense / 2)) * 2;
			d_stats.health -= damage;
			std::cout << a_stats.name << " critical strikes " << d_stats.name << " for " << damage << " damage" << std::endl;
		}
		else
		{
			damage = rand() % 5 + (a_stats.strenght * 2) - (d_stats.defense / 2);
			d_stats.health -= damage;
			std::cout << a_stats.name << " attacks " << d_stats.name << " for " << damage << " damage" << std::endl;
		}
	}
};