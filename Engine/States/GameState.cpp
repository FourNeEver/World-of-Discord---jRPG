#include "GameState.hpp"

void GameState::ECSinit()
{
	cardinal.Init();

	cardinal.RegisterComponent<Transform>();
	cardinal.RegisterComponent<Sprite>();
	cardinal.RegisterComponent<Physical>();
	cardinal.RegisterComponent<Animated>();
	cardinal.RegisterComponent<Collider>();
	cardinal.RegisterComponent<Statistics>();

	renderer = cardinal.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(cardinal.GetComponentType<Transform>());
		signature.set(cardinal.GetComponentType<Sprite>());
		cardinal.SetSystemSignature<RenderSystem>(signature);
	}
	controler = cardinal.RegisterSystem<ControlSystem>();
	{
		Signature signature;
		signature.set(cardinal.GetComponentType<Physical>());
		signature.set(cardinal.GetComponentType<Animated>());
		cardinal.SetSystemSignature<ControlSystem>(signature);
	}
	physics = cardinal.RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(cardinal.GetComponentType<Transform>());
		signature.set(cardinal.GetComponentType<Physical>());
		signature.set(cardinal.GetComponentType<Collider>());
		cardinal.SetSystemSignature<PhysicsSystem>(signature);
	}
	animator = cardinal.RegisterSystem<AnimationSystem>();
	{
		Signature signature;
		signature.set(cardinal.GetComponentType<Sprite>());
		signature.set(cardinal.GetComponentType<Animated>());
		cardinal.SetSystemSignature<AnimationSystem>(signature);
	}
	collider = cardinal.RegisterSystem<CollisionSystem>();
	{
		Signature signature;
		signature.set(cardinal.GetComponentType<Sprite>());
		signature.set(cardinal.GetComponentType<Collider>());
		cardinal.SetSystemSignature<CollisionSystem>(signature);
	}
	battler = cardinal.RegisterSystem<BattleSystem>();
	{
		Signature signature;
		signature.set(cardinal.GetComponentType<Collider>());
		signature.set(cardinal.GetComponentType<Statistics>());
		signature.set(cardinal.GetComponentType<Sprite>());
		cardinal.SetSystemSignature<BattleSystem>(signature);
	}

	
	int map[16][16];
	std::ifstream ifs("Resources/Map/Test.map");
	if (ifs.is_open())
	{
		for(int x = 0; x <= 15; x++)
		{
			for (int y = 0; y <= 15; y++)
			{

				ifs >> map[x][y];
				ifs.ignore();
			}
		}

	}

	int y = 0;
	int x = 0;
	for(auto& tile:tile_map)
	{
		tile = cardinal.CreateEntity();
		if (map[x][y] == 1)
		{
			cardinal.AddComponent(tile, Sprite{ sf::Texture(textures["BRICK"]),sf::IntRect(0,0,64,64) });
			cardinal.AddComponent(tile, Collider{ "TILE",64,64 });
		}
		else
		{
			cardinal.AddComponent(tile, Sprite{ sf::Texture(textures["GRASS"]),sf::IntRect(0,0,64,64) });
		}
		
		cardinal.AddComponent(tile, Transform{ sf::Vector2f(64 * y,64 * x),0,sf::Vector2f(1,1) });
		y++;
		if(y>=16)
		{
			y = 0;
			x++;
		}
	}


	enemy = cardinal.CreateEntity();
	cardinal.AddComponent(enemy, Transform{ sf::Vector2f(200,200),0,sf::Vector2f(2,2) });
	cardinal.AddComponent(enemy, Sprite{ textures["ENEMY_SHEET"] , sf::IntRect(0, 0, 32, 32) });
	cardinal.AddComponent(enemy, Collider{ "ENEMY",64,64,sf::Vector2f(0,0) });
	cardinal.AddComponent(enemy, Statistics{ "Human",1,0,0,40,40,5,3,6,4,3 });
	
	player = cardinal.CreateEntity();
	cardinal.AddComponent(player, Transform{sf::Vector2f(100,100),0,sf::Vector2f(2,2)});
	cardinal.AddComponent(player, Sprite{ textures["PLAYER_SHEET"] , sf::IntRect(0, 0, 32, 32) });
	cardinal.AddComponent(player, Physical{ sf::Vector2f(0,0),10.f,5.0f,200.f,sf::Vector2f(0,0),true});
	cardinal.AddComponent(player, Animated{"IDLE","Resources/Animations/player.animate"});
	cardinal.AddComponent(player, Collider{"PLAYER",32,64,sf::Vector2f(0,32)});
	cardinal.AddComponent(player, Statistics{ "Human",1,0,10,60,60,7,5,10,7,6 });
	
	renderer->init(&cardinal);
	animator->init(&cardinal);
	collider->init(&cardinal);

	
}



void GameState::initialize()
{
	view.setSize(sf::Vector2f(1280, 720));

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
	if (!textures["ENEMY_SHEET"].loadFromFile("Resources/Sprites/Characters/Enemy_texture.png"))
		throw"ERROR::GAME_STATE::COULD_NOT_LOAD_CHARACTER_TEXTURE";
	if (!textures["BRICK"].loadFromFile("Resources/Map/Pixel Brick 64.png"))
		throw"ERROR::GAME_STATE::COULD_NOT_LOAD_TILESET";
	if (!textures["GRASS"].loadFromFile("Resources/Map/Pixel GRASS 64.png"))
		throw"ERROR::GAME_STATE::COULD_NOT_LOAD_TILESET";
	

	

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
	{
		exit();
		window->setView(sf::View(sf::FloatRect(0, 0, 1280, 720)));
	}

	collider->collide(&cardinal, &player);

	
	collider->update(&cardinal);
	controler->update(&cardinal, &keybinds);
	physics->update(dt, &cardinal);
	animator->update(&cardinal,dt);
	renderer->update(&cardinal);



	//Debug
	//std::cout << cardinal.GetComponent<Physical>(player).velocity.x << " " << cardinal.GetComponent<Physical>(player).velocity.y << std::endl;

}

void GameState::render(sf::RenderTarget* target)
{
	window->clear();

	renderer->render(&cardinal, window);
	
	//*Debug* shows hitboxes
	//collider->render(&cardinal, window);

	view.setCenter(cardinal.GetComponent<Transform>(player).position);
	window->setView(view);
	
	
}

