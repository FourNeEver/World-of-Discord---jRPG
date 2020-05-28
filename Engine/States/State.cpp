#include "State.hpp"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
	: window(window),states(states)
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

void State::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosWiew = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::exit()
{
	active = false;
}
