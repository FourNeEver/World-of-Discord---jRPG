#include "SettingState.hpp"

void SettingState::initialize()
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
		throw("ERROR::SETTINGS_STATE::FAIL_TO_LOAD_BACKGROUND_TEXTURE");
	}

	background.setTexture(&backgroundTexture);

	if (!font.loadFromFile("Resources/Fonts/arial.ttf"))
	{
		throw("ERROR::SETTINGS_eSTATE::COULD NOT LOAD FONT");
	}
	
	resolutions.at(0) = new Resolution(sf::Vector2u(640, 480), "SD 640x480",0);
	resolutions.at(1) = new Resolution(sf::Vector2u(1280, 720), "HD 1280x720",1);
	resolutions.at(2) = new Resolution(sf::Vector2u(1920, 1080), "FHD 1920x1080",2);

	for (auto& r : resolutions)
	{
		if (window->getSize() == r->resx)
			res_counter = r->pos;
	}
	
	buttons["RESOLUTION"] = new Button(810.f, 280.f, 150.f, 50.f, &font, resolutions.at(res_counter)->name,
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));
	
	buttons["RESOLUTION_UP"] = new Button(1020.f, 270.f, 50.f, 50.f, &font, ">",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));
	
	buttons["RESOLUTION_DOWN"] = new Button(750.f, 270.f, 50.f, 50.f, &font, "<",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));

	//buttons["SETTINGS"] = new Button(1100.f, 340.f, 150.f, 50.f, &font, "Settings",
	//	30,
	//	sf::Color(70, 70, 70, 200),
	//	sf::Color(150, 150, 150, 255),
	//	sf::Color(20, 20, 20, 0),
	//	sf::Color(70, 70, 70, 0),
	//	sf::Color(150, 150, 150, 0),
	//	sf::Color(20, 20, 20, 0));


	buttons["BACK"] = new Button(810.f, 400.f, 150.f, 50.f, &font, "Back",
		30,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));


	//buttons["EDITOR"] = new Button(20, 650, 150, 50, &font, "Editor",
	//	30,
	//	sf::Color(70, 70, 70, 200),
	//	sf::Color(150, 150, 150, 255),
	//	sf::Color(20, 20, 20, 0),
	//	sf::Color(70, 70, 70, 0),
	//	sf::Color(150, 150, 150, 0),
	//	sf::Color(20, 20, 20, 0));


}

SettingState::SettingState(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supportedKeys)
	: State(window, states, supportedKeys)
{
	initialize();
}

SettingState::~SettingState()
{
}

void SettingState::update(const float& dt)
{

	
	/*Update all buttons in this state and their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosWiew);
	}

	
	
	//New Game
	if (buttons["RESOLUTION_UP"]->isPressed())
	{
		if (res_counter == 2)
			res_counter = 0;
		else
			res_counter++;
		
		buttons["RESOLUTION"]->change(resolutions.at(res_counter)->name);
		window->setSize(resolutions.at(res_counter)->resx);
		window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - resolutions.at(res_counter)->resx.x/2, sf::VideoMode::getDesktopMode().height / 2 - resolutions.at(res_counter)->resx.y/2));
	}

	if (buttons["RESOLUTION_DOWN"]->isPressed())
	{
		if (res_counter == 0)
			res_counter = 2;
		else
			res_counter--;
		buttons["RESOLUTION"]->change(resolutions.at(res_counter)->name);
		window->setSize(resolutions.at(res_counter)->resx);
		window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - resolutions.at(res_counter)->resx.x/2, sf::VideoMode::getDesktopMode().height / 2 - resolutions.at(res_counter)->resx.y/2));
	}

	//if (buttons["SETTINGS"]->isPressed())
	//{
	//	states->push(new)
	//}

	//Quit the game
	if (buttons["BACK"]->isPressed())
	{
		exit();
	}

	updateInput();
}

void SettingState::render(sf::RenderTarget* target)
{
	window->draw(background);

	for (auto& it : buttons)
	{
		it.second->render(window);
	}
}

