#pragma once
#include <SDL\SDL.h>;
#include <gl\glew.h>;
#include <string>;

using namespace std;

enum WindowsFlags {
	INVISIBLE = 0x1,
	FULLSCREEN = 0x2,
	BORDERLES = 0x4
};


class Window
{
private:
	SDL_Window *window;
	int screenWidth;
	int screenHeigth;
public:
	Window();
	~Window();
	void swapWindow();
	int getScreenWidth() {
		return screenWidth;
	}

	int getScreenHeight() {
		return screenHeigth;
	}
	int create(string _windowName,
		int _screenWidth,
		int _screenHeight,
		unsigned int currentFlags
	);
};

