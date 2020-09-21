#include"game.h"
#include<time.h>

int main()
{
	srand(static_cast<unsigned>(time(0)));
	
	game Game;

	Game.run();

	return 0;
}