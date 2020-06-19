#include "GUI.hpp"

BattleGUI::BattleGUI(sf::RenderWindow& window, sf::Texture& background_tex, std::list<Entity*> entites)
	: texture_background(background_tex),heroes_list(entites)
{
	background.setTexture(&texture_background);

	background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y * 0.3));
	background.setPosition(sf::Vector2f(0, window.getSize().y * 0.7));
	
}
