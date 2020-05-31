#include "State.hpp"

State::State(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supportedKeys)
	: window(window),states(states),supportedKeys(supportedKeys)
{
	active = true;
}

State::~State()
{
}

const bool& State::isActive() const
{
	return active;
}

void State::updateInput()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosWiew = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::exit()
{
	active = false;
}
