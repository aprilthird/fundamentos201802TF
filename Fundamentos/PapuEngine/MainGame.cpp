#include "MainGame.h"
#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"
#include <ctime>
#include <random>

using namespace std;

void MainGame::run() {
	init();
	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Holi :D", _witdh, _height, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	initLevel();
	initShaders();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randomPosX(
		1, _levels[_currenLevel]->getWidth() - 2);

	std::uniform_int_distribution<int>randomPosY(
		1, _levels[_currenLevel]->getHeight() - 2);


	for (int i = 0; i < 
			_levels[_currenLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randomPosX(randomEngine)*TILE_WIDTH,
			randomPosY(randomEngine)*TILE_WIDTH);
		_humans.back()->init(10.0f, pos);
	}




}

void MainGame::initLevel() {
	_levels.push_back(new Level("Levels/level1.txt"));
	_player = new Player();
	_currenLevel = 0;
	_player->init(10.0f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager);
	//_humans.push_back(_player);
	_spriteBacth.init();
}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1,GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();
	_levels[_currenLevel]->draw();
	_player->draw(_spriteBacth);
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_spriteBacth);
	}

	_spriteBacth.end();
	_spriteBacth.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	_program.unuse();
	_window.swapBuffer();
}

void MainGame::procesInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(event.motion.x,event.motion.y);
			break;
			case  SDL_KEYUP:
				_inputManager.releaseKey(event.key.keysym.sym);
				break;
			case  SDL_KEYDOWN:
				_inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(event.button.button);
				break;
		}
		if (_inputManager.isKeyPressed(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords =  _camera.convertScreenToWorl(_inputManager.getMouseCoords());
			cout << mouseCoords.x << " " << mouseCoords.y << endl;

			glm::vec2 playerPosition(0, 0);

			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets.emplace_back(playerPosition, direction, 1.0f,1000);
		}
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		_camera.update();
		_time += 0.002f;
		updateAgents();
		_camera.setPosition(_player->getPosition());
	}
}

void MainGame::updateAgents() {
	_player->update(_levels[_currenLevel]->getLevelData(),
		_humans, _zombies);
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(
			_levels[_currenLevel]->getLevelData(),
				_humans,_zombies
			);
		_humans[i]->collideWithOther(_player);
	}

	//
}

MainGame::MainGame(): 
					  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0),
					  _player(nullptr)
{
	_camera.init(_witdh, _height);
}


MainGame::~MainGame()
{
}
