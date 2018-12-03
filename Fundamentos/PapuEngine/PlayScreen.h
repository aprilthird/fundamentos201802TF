#pragma once
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "SpriteBacth.h"
#include "Background.h"
#include "GLTexture.h"
#include "SpriteFont.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Alien.h"
#include "AlienBullet.h"
#include <ctime>

class PlayScreen: public IGameScreen
{
private:
	GLS_Program _program;
	Camera2D _camera2D;
	Background* _background;
	Window* _window = nullptr;
	SpriteBacth _spriteBatch;
	SpriteBacth _hudBach;
	Camera2D _hudCamera;
	SpriteFont* _spriteFont;
	Player* _jugador;
	std::vector<PlayerBullet*> _playerBullets;
	std::vector<Alien*> _aliens;
	std::vector<AlienBullet*> _alienBullets;
	clock_t _beginTime;
	clock_t _endTime;
	int _roundNumber;
	long int _prevAnimatedD;
	long int _ellapsedTimeD;
	long int _ellapsedTimeI;
	long int _prevShootTime;
	bool _gameOver = false;
	bool _shoot;
	void drawHUD();
public:
	PlayScreen(Window* window);
	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	virtual void initGUI() override;
	virtual void draw() override;
	virtual void update()override;
	virtual void initSystem()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;
	virtual void checkInput() override;
	void initRound();
	~PlayScreen();
};

