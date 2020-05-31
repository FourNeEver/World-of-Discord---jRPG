#pragma once

#include "State.hpp"
#include "../ECS/ECS.hpp"

class GameState : public State
{
private:
	Coordinator cardinal;
	Signature signature;
	std::shared_ptr<RenderSystem> renderer;
	std::shared_ptr<ControlSystem> controler;
	std::shared_ptr<PhysicsSystem> physics;
	std::shared_ptr<AnimationSystem> animator;

	std::map<std::string, sf::Texture> textures;

	void ECSinit();
	void initialize();

public:
	Entity player;
	
	GameState(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

