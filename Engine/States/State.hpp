#pragma once
#include "../Libraries.hpp"
#include "../ECS/ECS.hpp"

class State
{
private:

protected:
	
	sf::RenderWindow* window;
	std::stack<State*>* states;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	bool active;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosWiew;


	//Resources

	//Functions

public:
	State(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supportedKeys);
	virtual ~State();

	const bool& isActive() const;

	void exit();

	void updateInput();
	
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	
};


