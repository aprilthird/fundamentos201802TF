#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "GLS_Program.h"
#include "Sprite.h"
#include "Camera2D.h";
#include <vector>
#include <iostream>;
#include "Window.h";

enum class GameState
{
	PLAY, EXIT
};


class MainGame
{
private:
	int _witdh;
	int _height;
	float _time;
	Window _window;
	void init();
	void procesInput();
	Camera2D camera2D;
	GLS_Program _program;
	vector<Sprite*> _sprites;
	
public:
	MainGame();
	~MainGame();
	GameState _gameState;
	void initShaders();
	void run();
	void draw();
	void update();
};

