#pragma once

#include "State.hpp"
#include "../ECS/ECS.hpp"

class GameState : public State
{
private:
	Coordinator cardinal;

	sf::View view;
	
	std::shared_ptr<RenderSystem> renderer;
	std::shared_ptr<ControlSystem> controler;
	std::shared_ptr<PhysicsSystem> physics;
	std::shared_ptr<AnimationSystem> animator;
	std::shared_ptr<CollisionSystem> collider;
	std::shared_ptr<BattleSystem> battler;

	std::map<std::string, sf::Texture> textures;

	void ECSinit();
	void initialize();

public:
	Entity player;
	Entity enemy;
	std::array<Entity,256> tile_map;
	std::vector<Entity> collider_map;
	
	
	GameState(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;

	void load_map(const char* path);
	
};

