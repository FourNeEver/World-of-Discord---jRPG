#pragma once
#include "ECS/ECS.hpp"

class Battle
{
	BattleGUI* battle_gui;
	sf::Font font;
	sf::Texture gui_background;
	
	sf::RectangleShape background;
	sf::Texture background_texture;
	sf::RectangleShape GUI_background;
	sf::Texture GUI_texture;

	std::list<Entity*> living;
	std::list<Entity*>::iterator current_hero;
	std::list<Entity*> action_queue;
	bool fighting = true;
	bool action_avaible;
	bool enemy_alive = false;

	Coordinator* cardinal;
	Entity* player;
	Entity* enemy;
	std::shared_ptr<BattleSystem> battler;
	std::shared_ptr<RenderSystem> renderer;
	std::shared_ptr<AnimationSystem> animator;
	sf::RenderWindow* window;
	std::vector<Entity>* enemies;
	std::map<int, Entity>* heroes;
	std::map<int, Ability>* all_abs;

	Statistics h_stats;
	Sprite h_sprite;
	
	sf::Clock loading;
	sf::Clock DeltaTime;
	sf::Time Elapsed;
	sf::Time Timer;

	sf::Vector2f mousePosWiew;

	sf::Vector2f player_pos;
	sf::Vector2f enemy_pos;
	
	
public:
	Battle(Coordinator* cardinal, Entity* player, Entity* enemy, std::shared_ptr<BattleSystem> battler, std::shared_ptr<RenderSystem> renderer, std::shared_ptr<AnimationSystem> animator, sf::RenderWindow* window, std::vector<Entity>* enemies, std::map<int, Entity>* heroes, std::map<int, Ability>* all_abs);
	void battle();
};

inline Battle::Battle(Coordinator* _cardinal, Entity* _player, Entity* _enemy, std::shared_ptr<BattleSystem> _battler, std::shared_ptr<RenderSystem> _renderer, std::shared_ptr<AnimationSystem> _animator,
	sf::RenderWindow* _window, std::vector<Entity>* _enemies, std::map<int, Entity>* _heroes,
	std::map<int, Ability>* _all_abs)
	: cardinal(_cardinal), player(_player), enemy(_enemy), battler(_battler), renderer(_renderer),animator(_animator), window(_window), enemies(_enemies), heroes(_heroes), all_abs(_all_abs)
{

	//Loading fonts
	if (!font.loadFromFile("Resources/Fonts/arial.ttf"))
	{
		throw("ERROR::BATTLE::COULD NOT LOAD FONT");
	}
	
	///Loading backgrounds
    //Main background
	if (!background_texture.loadFromFile("Resources/Images/Backgrounds/pixel_forest.png"))
	{
		throw"ERROR::BATTLE::FAIL_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setSize(sf::Vector2f(window->getSize()));
	background.setPosition(sf::Vector2f(0, -185));
	background.setTexture(&background_texture);

	//GUI Background
	if (!GUI_texture.loadFromFile("Resources/Images/Backgrounds/action_gui.jpg"))
	{
		throw"ERROR::BATTLE::FAIL_TO_LOAD_BACKGROUND_TEXTURE";
	}
	GUI_background.setSize(sf::Vector2f(window->getSize().x, 200));
	GUI_background.setTexture(&GUI_texture);
	GUI_background.setPosition(sf::Vector2f(0, window->getSize().y - GUI_background.getSize().y));
	//GUI_background.setFillColor(sf::Color(140,140,60,255));
	GUI_background.setOutlineColor(sf::Color::Black);
	GUI_background.setOutlineThickness(1);

	//Getting some components
	auto& p_transform = cardinal->GetComponent<Transform>(*player);
	auto& e_transform = cardinal->GetComponent<Transform>(*enemy);

	//Saving previous position
	player_pos = p_transform.position;
	enemy_pos = cardinal->GetComponent<Transform>(*enemy).position;

	//Player team init
	cardinal->GetComponent<Animated>(*player).currentAnimation = "IDLE_SIDE";
	p_transform.position = sf::Vector2f(1100, 450);
	int place = 1;
	for (auto& t : cardinal->GetComponent<Team>(*player).team)
	{
		cardinal->GetComponent<Sprite>(heroes->at(t)).isVisible = true;
		if (!(place % 2))
			cardinal->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(p_transform.position.x, p_transform.position.y - (50 * place));
		else
			cardinal->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(p_transform.position.x - 70, p_transform.position.y - (50 * place));
		std::cout << cardinal->GetComponent<Statistics>(heroes->at(t)).name << std::endl;
		place++;
	}

	//Enemy team init
	cardinal->GetComponent<Animated>(*enemy).currentAnimation = "IDLE_SIDE";
	e_transform.position = sf::Vector2f(200, 400);

	place = 1;
	for (auto& t : cardinal->GetComponent<Team>(*enemy).team)
	{
		cardinal->GetComponent<Sprite>(heroes->at(t)).isVisible = true;
		if (!(place % 2))
			cardinal->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(e_transform.position.x, e_transform.position.y - (50 * place));
		else
			cardinal->GetComponent<Transform>(heroes->at(t)).position = sf::Vector2f(e_transform.position.x - 70, e_transform.position.y - (50 * place));
		cardinal->GetComponent<Statistics>(heroes->at(t)).flag = "ENEMY";
		std::cout << cardinal->GetComponent<Statistics>(heroes->at(t)).name << std::endl;
		place++;
	}

	//Renderer update
	renderer->update(cardinal);

	//GUI update
	cardinal->GetComponent<GUI>(*player).health_bar.update_origin(cardinal->GetComponent<Sprite>(*player).sprite.getGlobalBounds());
	cardinal->GetComponent<GUI>(*enemy).health_bar.update_origin(cardinal->GetComponent<Sprite>(*enemy).sprite.getGlobalBounds());

	//Teams set up
	for (auto& t : cardinal->GetComponent<Team>(*player).team)
	{
		cardinal->GetComponent<GUI>(heroes->at(t)).health_bar.update_origin(cardinal->GetComponent<Sprite>(heroes->at(t)).sprite.getGlobalBounds());
	}

	for (auto& t : cardinal->GetComponent<Team>(*enemy).team)
	{
		cardinal->GetComponent<GUI>(heroes->at(t)).health_bar.update_origin(cardinal->GetComponent<Sprite>(heroes->at(t)).sprite.getGlobalBounds());
	}

	//Gathering living entities
	living.emplace_back(player);
	living.emplace_back(enemy);
	for (auto& t : cardinal->GetComponent<Team>(*player).team)
	{
		living.emplace_back(&heroes->at(t));
	}
	for (auto& t : cardinal->GetComponent<Team>(*enemy).team)
	{
		living.emplace_back(&heroes->at(t));
	}

	std::list<Entity*> action_queue = living;

	battle_gui = new BattleGUI(cardinal, window, &font, gui_background, action_queue, heroes, enemy, player, all_abs);

	//Ending initialization
	cardinal->GetComponent<Combat>(*player).is_initialized = true;
	
	std::cout << "Battle initialized in " << loading.getElapsedTime().asSeconds() << " seconds" << std::endl;

}

inline void Battle::battle()
{
	auto& p_team = cardinal->GetComponent<Team>(*player);
	auto& e_team = cardinal->GetComponent<Team>(*enemy);
	auto& p_stats = cardinal->GetComponent<Statistics>(*player);
	auto& e_stats = cardinal->GetComponent<Statistics>(*enemy);
	
	while (fighting)
	{
		//Queue set up
		action_queue = living;

		battler->compare_agility(cardinal, action_queue);

		//std::cout << "Battle order: " << std::endl;
		//for (auto& hero : action_queue)
		//{
		//	std::cout << coordinator->GetComponent<Statistics>(*hero).name << std::endl;;
		//}
		while (!action_queue.empty() && fighting)
		{
			//Timer reset
			Elapsed = DeltaTime.restart();

			//Mouse Position Update
			mousePosWiew = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			//std::cout << mousePosWiew.x << " " << mousePosWiew.y << std::endl;

			//Input handling
			//Debug input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				fighting = false;


			//Pulling current hero stats;
			current_hero = action_queue.begin();

			h_stats = cardinal->GetComponent<Statistics>(**current_hero);
			h_sprite = cardinal->GetComponent<Sprite>(**current_hero);




			//Actions
			if (h_stats.flag == "ALLY")
			{
				if (battle_gui->enemy_ptr.at(0)->isPressed())
				{
					battler->phys_attack(h_stats, cardinal->GetComponent<Statistics>(*enemy));
					action_avaible = false;
					action_queue.pop_front();
				}
				for (auto& e : e_team.team)
				{
					if (battle_gui->enemy_ptr.at(e)->isPressed())
					{

						battler->phys_attack(h_stats, cardinal->GetComponent<Statistics>(heroes->at(e)));
						action_avaible = false;
						action_queue.pop_front();
					}
				}
			}
			if (h_stats.flag == "ENEMY")
			{
				Timer += DeltaTime.getElapsedTime();
				if (Timer.asMicroseconds() > 20000)
				{
					battler->phys_attack(h_stats, p_stats);
					action_avaible = true;
					Timer = sf::Time::Zero;
					action_queue.pop_front();
				}
			}


			//Killing heroes
			for (auto& l : living)
			{
				if (cardinal->GetComponent<Statistics>(*l).health <= 0)
				{
					living.remove(l);
					break;
				}
			}
			//Removing dead heroes from queue
			for (auto& a : action_queue)
			{
				if (cardinal->GetComponent<Statistics>(*a).health <= 0)
				{
					action_queue.remove(a);
					break;
				}
			}

			//Removing buttons
			if (cardinal->GetComponent<Statistics>(*enemy).health <= 0)
				battle_gui->enemy_ptr.at(0)->disable();
			for (auto& e : e_team.team)
			{
				if (cardinal->GetComponent<Statistics>(heroes->at(e)).health <= 0)
					battle_gui->enemy_ptr.at(e)->disable();
			}

			//Fight ending
			if (e_stats.health > 0)
				enemy_alive = true;
			for (auto& e : e_team.team)
			{
				if (cardinal->GetComponent<Statistics>(heroes->at(e)).health > 0)
					enemy_alive = true;
			}
			if (!enemy_alive)
				fighting = false;


			///Systems update

			//Bars update
			for (auto& l : living)
			{
				cardinal->GetComponent<GUI>(*l).health_bar.update(cardinal->GetComponent<Statistics>(*l).health);
			}

			//GUI Update
			battle_gui->update(mousePosWiew, h_stats.name, h_sprite.sprite.getGlobalBounds(), h_stats.flag, h_stats.abilities);

			//Coordinator system update

			animator->update(cardinal, Elapsed.asSeconds());
			renderer->update(cardinal);



			///Display
			//Preparations
			window->clear();

			//Background render
			window->draw(background);


			//Sprite render
			for (auto& l : living)
			{
				window->draw(cardinal->GetComponent<Sprite>(*l).sprite);
			}

			//Bars Render
			for (auto& l : living)
			{
				cardinal->GetComponent<GUI>(*l).health_bar.render(window);
			}

			//GUI Render
			window->draw(GUI_background);

			battle_gui->render(window);

			//Display window
			window->display();

			//View set
			window->setView(sf::View(sf::FloatRect(0, 0, 1280, 720)));


		}

	}

	//Hiding team sprites
	for (auto& t : p_team.team)
	{
		cardinal->GetComponent<Sprite>(heroes->at(t)).isVisible = false;
	}
	for (auto& t : e_team.team)
	{
		cardinal->GetComponent<Sprite>(heroes->at(t)).isVisible = false;
	}

	//Revertiong positions
	cardinal->GetComponent<Transform>(*player).position = player_pos;
	cardinal->GetComponent<Transform>(*enemy).position = enemy_pos;

	//Killing enemy
	cardinal->GetComponent<Collider>(*enemy).colliding.at("ACTION") = false;
	e_stats.alive = false;
	
	//Stopping the player
	cardinal->GetComponent<Physical>(*player).velocity = sf::Vector2f(0, 0);

	//Ending battle
	cardinal->GetComponent<Combat>(*player).in_combat = false;
}

