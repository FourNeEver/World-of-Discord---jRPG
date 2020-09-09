#pragma once

#include "Libraries.hpp"
#include "Button.hpp"
#include "States/SettingState.hpp"

class Pause
{
	bool pause_ = false;
	bool exit = false;
	sf::RenderWindow& window_;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, Button*> buttons;

public:
	Pause(bool isPaused, sf::RenderWindow& window);

	void update(const float& dt);
	void render(sf::RenderWindow& window);

	void pause() { pause_ = true; }
	void unpause() { pause_ = false; }
	bool isExiting() { return exit; };
	bool isPaused() { return pause_; };
};

inline Pause::Pause(bool isPaused, sf::RenderWindow& window) : pause_(isPaused), window_(window)
{
	background.setSize(sf::Vector2f(window.getSize()));

	if (!backgroundTexture.loadFromFile("Resources/Images/Backgrounds/mainmenu_bg.jpg"))
	{
		throw"ERROR::MAIN_MENU_STATE::FAIL_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setTexture(&backgroundTexture);

	if (!font.loadFromFile("Resources/Fonts/arial.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
	
	buttons["RESUME"] = new Button(1100.f, 280.f, 150.f, 50.f, &font, "Resume",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));

	buttons["SAVE"] = new Button(1100.f, 340.f, 150.f, 50.f, &font, "Save",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));


	buttons["EXIT"] = new Button(1100.f, 400.f, 150.f, 50.f, &font, "Quit",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));
}

inline void Pause::update(const float& dt)
{
	sf::Vector2f mousePosWiew = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
	
	for (auto& it : buttons)
	{
		it.second->update(mousePosWiew);
	}

	//New Game
	if (buttons["RESUME"]->isPressed())
	{
		unpause();
	}

	if (buttons["SAVE"]->isPressed())
	{
		std::cout << "NOT IMPLEMENTED" << std::endl;
	}

	//Quit the game
	if (buttons["EXIT"]->isPressed())
	{
		exit = true;
	}
}

inline void Pause::render(sf::RenderWindow& window)
{
	window.draw(background);

	for (auto& it : buttons)
	{
		it.second->render(&window);
	}

	
}
