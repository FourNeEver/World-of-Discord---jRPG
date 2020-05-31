#include "GameState.hpp"

void GameState::ECSinit()
{
	cardinal.Init();

	cardinal.RegisterComponent<Transform>();
	cardinal.RegisterComponent<Display>();
	cardinal.RegisterComponent<Physical>();
	cardinal.RegisterComponent<Animated>();

	renderer = cardinal.RegisterSystem<RenderSystem>();
	controler = cardinal.RegisterSystem<ControlSystem>();
	physics = cardinal.RegisterSystem<PhysicsSystem>();
	animator = cardinal.RegisterSystem<AnimationSystem>();
	
	signature.set(cardinal.GetComponentType<Transform>());
	signature.set(cardinal.GetComponentType<Display>());
	signature.set(cardinal.GetComponentType<Physical>());
	signature.set(cardinal.GetComponentType<Animated>());
	
	cardinal.SetSystemSignature<RenderSystem>(signature);
	cardinal.SetSystemSignature<ControlSystem>(signature);
	cardinal.SetSystemSignature<PhysicsSystem>(signature);
	cardinal.SetSystemSignature<AnimationSystem>(signature);

	//std::vector<Entity> Player_Team(4);

	player = cardinal.CreateEntity();
	cardinal.AddComponent(player, Transform{sf::Vector2f(100,100),0,sf::Vector2f(2,2)});
	cardinal.AddComponent(player, Display{sf::Sprite(textures["PLAYER_SHEET"])});
	cardinal.AddComponent(player, Physical{ sf::Vector2f(0,0),10.f,2.0f,200.f,sf::Vector2f(0,0),true});
	cardinal.AddComponent(player, Animated{textures["PLAYER_SHEET"], "IDLE","Resources/Animations/player.animate"});

	animator->init(&cardinal);
}

void GameState::initialize()
{

	std::ifstream ifs("Config/gamestate_keybinds.ini");
	if (ifs.is_open())
	{
		std::string key;
		std::string key2;
		while (ifs >> key >> key2)
		{
			keybinds[key] = supportedKeys->at(key2);
		}
	}

	ifs.close();
	
	if (!textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Characters/Knight.png"))
		throw"ERROR::GAME_STATE::COULD_NOT_LOAD_CHARACTER_TEXTURE";

	

	ECSinit();

}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supportedKeys)
	: State(window,states,supportedKeys)
{
	initialize();
}

GameState::~GameState()
{
	
}

void GameState::update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
		exit();



	controler->update(&cardinal, &keybinds);
	physics->update(dt, &cardinal);
	animator->update(&cardinal,dt);
	renderer->update(&cardinal);

	std::cout << cardinal.GetComponent<Transform>(player).position.x << " " << cardinal.GetComponent<Transform>(player).position.y << std::endl;
	
}

void GameState::render(sf::RenderTarget* target)
{
	renderer->render(&cardinal, window);
	
	
}
