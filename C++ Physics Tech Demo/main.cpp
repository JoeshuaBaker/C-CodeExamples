#include "Game.h"

int main(int argc, char** argv)
{
	std::cout << argc << std::endl;
    Game game(argc);   
    return game();
}
