#include "GameState.hpp"

void GameState::ECSinit()
{
	cardinal.Init();

	cardinal.RegisterComponent<Transform>();
	cardinal.RegisterComponent<Display>();

	renderer = cardinal.RegisterSystem<RendererSystem>();

	signature.set(cardinal.GetComponentType<Transform>());
	signature.set(cardinal.GetComponentType<Display>());
	cardinal.SetSystemSignature<RendererSystem>(signature);

	//std::vector<Entity> Player_Team(4);

	player = cardinal.CreateEntity();
	cardinal.AddComponent(player, Transform{sf::Vector2f(100,100),0,sf::Vector2f(1,1)});
	cardinal.AddComponent(player, Display{sf::Sprite(textures["PLAYER_SHEET"]),false });
	
}

void GameState::initialize()
{
	if (!textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Characters/Example_character.png"))
		throw"ERROR::GAME_STATE::COULD_NOT_LOAD_CHARACTER_TEXTURE";

	ECSinit();
	
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window,states)
{
	initialize();
}

GameState::~GameState()
{
}

void GameState::update(const float& dt)
{

	renderer->update(dt,&cardinal);
	
}

void GameState::render(sf::RenderTarget* target)
{
	window->clear(sf::Color::Red);
	window->draw(cardinal.GetComponent<Display>(player).sprite);
	
}
