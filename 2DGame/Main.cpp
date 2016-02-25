#include "MainGame.h"
// The entry point of the program that SDL provides.
// Basiclly just don't ask and make the main function like "int main(int argc, char** argv)", good for you.
// "argc" means the count of command line.
// "argv" is the list of the arguments, just a array of c_str().
int main(int argc, char** argv) {
	MainGame mainGame;
	mainGame.RunGame();
	return 0;
}