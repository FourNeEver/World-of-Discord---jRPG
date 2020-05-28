#include "Game.hpp"



void Game::initialize()
{
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Test");

    states.push(new MainMenuState(window, &states));
	
}

Game::Game()
{
    initialize();
}

Game::~Game()
{
    delete window;

    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}

void Game::update()
{
    Elapsed = DeltaTime.restart();

    while (window->pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            std::cout << "Closing Window" << std::endl;
            window->close();
        }
	}

    if (!states.empty())
    {
        states.top()->update(Elapsed.asSeconds());

        if (!states.top()->isActive())
        {
            states.top()->exit();
            delete states.top();
            states.pop();
        }
    }
    //Application end
    else
    {
        window->close();
    }
}

void Game::render()
{
    window->clear(sf::Color::Cyan);

    if (!states.empty())
        states.top()->render(window);

	
    window->draw(square);
	
    window->display();
}