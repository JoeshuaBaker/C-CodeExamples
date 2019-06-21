//Joeshua Baker
//Homework 5
//Completed 3/13/2016

#include "Game.h"

//Due to a problem with my compiler installation that I can't fix, I need to
//Stick this here for my program to compile. You can remove if it you need.
void *__gxx_personality_v0;

int main(int argc, char** argv)
{
	std::cout << argc << std::endl;
    Game game(argc);   
    return game();
}
