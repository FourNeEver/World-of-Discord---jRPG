#pragma once
#include "State.hpp"
#include "../Button.hpp"

struct Resolution
{
	Resolution(sf::Vector2u resx,std::string name,int pos)
		:resx(resx),name(name),pos(pos){}
	sf::Vector2u resx;
	std::string name;
	int pos;
};

class SettingState :
    public State
{


private:
	
	//Varaibles
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;
	std::array<Resolution*,3> resolutions;
	int res_counter = 1;
	//Functions
	void initialize();
public:
	SettingState(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supportedKeys);
	virtual ~SettingState();

	//Functions

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

