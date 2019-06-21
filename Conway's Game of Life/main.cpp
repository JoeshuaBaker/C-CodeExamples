#include "Conway.h"

//Due to a problem with my compiler installation that I can't fix, I need to
//Stick this here for my program to compile. You can remove if it you need.
void *__gxx_personality_v0;

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		cout << "Please provide a filename and number of rounds.";
		return -1;
	}
	
	string fileName(argv[1]);
	Conway game(fileName);
	int plays = atoi(argv[2]);
	game.play(plays);
	return 0;
}