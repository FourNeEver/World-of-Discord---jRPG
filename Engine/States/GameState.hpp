#pragma once

#include "State.hpp"
#include "../ECS/ECS.hpp"

class GameState : public State
{
private:
	Coordinator cardinal;
	Signature signature;
	std::shared_ptr<RendererSystem> renderer;

	std::map<std::string, sf::Texture> textures;

	void ECSinit();
	void initialize();

public:
	Entity player;
	
	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

