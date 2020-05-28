#pragma once

#include "Libraries.hpp"
#include "States/State.hpp"
#include "States/MainMenuState.hpp"
#include "ECS/ECS.hpp"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock DeltaTime;
	sf::Time Elapsed;

	sf::RectangleShape square;

	std::stack<State*> states;

	void initialize();
public:
	Game();
	virtual ~Game();

	bool isRunning() { return window->isOpen(); }
	
	void update();
	void render();
};

