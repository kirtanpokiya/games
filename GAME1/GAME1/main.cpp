#include<SFML/Graphics.hpp>
#include"Game.h"
#include <iostream>

int main()
{
	std::srand(static_cast<unsigned>(time(NULL)));
	Game game;
	while (game.running() && !game.getEndGame())
	{
		//update
		game.update();

		//Render
		game.render();
	}
	return 0;
}