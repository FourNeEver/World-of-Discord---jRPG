#pragma once

#include "Libraries.hpp"

enum button_states { BTN_IDLE, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;


	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;



public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text,
		unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color,
		sf::Color text_active_color, sf::Color idle_color, sf::Color hover_color,
		sf::Color active_color);
	~Button();

	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};