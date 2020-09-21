#include"Game.h"

int main()
{
	srand(static_cast<unsigned>(time(0)));

	Game game;

	//game loop
	while (game.running())
	{
		game.update();
		game.render();
	}

	return 0;
}