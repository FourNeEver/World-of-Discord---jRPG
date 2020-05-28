#pragma once
#include "../Libraries.hpp"
#include "../ECS/ECS.hpp"

class State
{
private:

protected:
	
	sf::RenderWindow* window;
	std::stack<State*>* states;
	

	bool active;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosWiew;


	//Resources

	//Functions

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	const bool& isActive() const;

	void exit();

	void updateMousePosition();
	
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	
};


