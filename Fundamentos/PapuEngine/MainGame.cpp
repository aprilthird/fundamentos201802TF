#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"

void MainGame::run() {
	init();
	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1, -1, 1, 1, "Textures/Paper_Mario_.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0, -1, 1, 1, "Textures/Paper_Mario_.png");
	update();
}
void MainGame::init() {
	_window.create("Camera2d", _witdh, _height, 0);
	initShaders();
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
	

	GLuint pLocation =_program.getUniformLocation("P");
	glm::mat4 cameraMatrix = camera2D.getCameraMatrix();

	
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, 
							&(cameraMatrix[0][0]));
	
	GLuint timeLocation = 
		_program.getUniformLocation("time");

	glUniform1f(timeLocation,_time);

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_time+=0.002;

	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}
	_program.unuse();
	_window.swapWindow();
}

void MainGame::procesInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float CAMERA_SCALE = 0.1f;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_w:
					camera2D.setPosition(
						camera2D.getPosition()
						- glm::vec2(0.0, CAMERA_SPEED)
					);
					break;
				case SDLK_s:
					camera2D.setPosition(
						camera2D.getPosition()
						+ glm::vec2(0.0, CAMERA_SPEED)
					);
					break;
				case SDLK_a:
					camera2D.setPosition(
						camera2D.getPosition()
						- glm::vec2(CAMERA_SPEED,0.0)
					);
					break;
				case SDLK_d:
					camera2D.setPosition(
						camera2D.getPosition()
						+ glm::vec2(CAMERA_SPEED, 0.0)
					);
					break;

				case SDLK_q:
					camera2D.setScale(
						camera2D.getScale() + CAMERA_SCALE);
					break;
				case SDLK_e:
					camera2D.setScale(
						camera2D.getScale() - CAMERA_SCALE);
					break;
				}
				break;
		}
	}

}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		camera2D.update();
		procesInput();
		draw();
		
	}
}


MainGame::MainGame():  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0)
{
	camera2D.init(_witdh, _height);
}


MainGame::~MainGame()
{
}
