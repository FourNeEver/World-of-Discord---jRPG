#include "MainMenuState.hpp"

#include "GameState.hpp"

void MainMenuState::initialize()
{

	std::ifstream ifs("Config/mainmenustate_keybinds.ini");
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
	
	background.setSize(sf::Vector2f(window->getSize()));

	if (!backgroundTexture.loadFromFile("Resources/Images/Backgrounds/mainmenu_bg.jpg"))
	{
		throw"ERROR::MAIN_MENU_STATE::FAIL_TO_LOAD_BACKGROUND_TEXTURE";
	}

	background.setTexture(&backgroundTexture);

	if (!font.loadFromFile("Resources/Fonts/arial.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
	
	buttons["GAME_STATE"] = new Button(1100.f, 280.f, 150.f, 50.f, &font, "New Game",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));

	buttons["SETTINGS"] = new Button(1100.f, 340.f, 150.f, 50.f, &font, "Settings",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));


	buttons["EXIT_STATE"] = new Button(1100.f, 400.f, 150.f, 50.f, &font, "Quit",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));


	buttons["EDITOR"] = new Button(20, 650, 150, 50, &font, "Editor",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));


}


MainMenuState::MainMenuState(sf::RenderWindow* window,std::stack<State*>* states, std::map<std::string, int>* supportedKeys)
	: State(window,states,supportedKeys)
{
	initialize();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update(const float& dt)
{

	/*Update all buttons in this state and their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosWiew);
	}

	//New Game
	if (buttons["GAME_STATE"]->isPressed())
	{
		states->push(new GameState(window, states,supportedKeys));
		std::cout << "Game open" << std::endl;
	}

	//Quit the game
	if (buttons["EXIT_STATE"]->isPressed())
	{
		exit();
	}
	
	updateInput();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	window->draw(background);

	for (auto& it : buttons)
	{
		it.second->render(window);
	}
}

