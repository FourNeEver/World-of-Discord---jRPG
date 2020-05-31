#pragma once
#include "State.hpp"
#include "../Button.hpp"

class MainMenuState
: public State
{
	

private:
	//Varaibles
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Functions
	void initialize();
public:
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	//Functions

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};


