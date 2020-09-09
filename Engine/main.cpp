
#include "ECS/ECS.hpp"
#include "Game.hpp"

Game* game;

int main()
{

    game = new Game();

    while (game->isRunning()) {

        game->update();
        game->render();

    }
	
    delete game;
	
	return 0;
}