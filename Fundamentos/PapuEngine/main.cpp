#include <SDL\SDL.h>
#include "MainGame.h"
#include "Engine.h";

int main(int argc,char** argv) {
	FD08::init();
	MainGame mainge;
	mainge.run();
	system("PAUSE");
	return 0;
}