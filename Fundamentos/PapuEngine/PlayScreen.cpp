#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"
#include "Constants.h"
#include <time.h>

PlayScreen::PlayScreen(Window* window):_window(window)
{
	_screenIndex = SCREEN_INDEX_GAME;
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	_spriteFont = new SpriteFont(PATH::FONTS::BITS8.c_str(), 64);
	_hudBach.init();
	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
}

void PlayScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void PlayScreen::destroy() {
	
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	srand(time(NULL));
	_background = new Background(PATH::BACKGROUNDS::GAME);
	initGUI();
	_roundNumber = 1;
	initRound();
}

void PlayScreen::update() {
	_camera2D.update();
	_endTime = clock();
	_ellapsedTimeD = int(_endTime - _beginTime) / (CLOCKS_PER_SEC / 10);
	_ellapsedTimeI = int(_endTime - _beginTime) / CLOCKS_PER_SEC;
	if (_ellapsedTimeD % 5 == 0 && _ellapsedTimeD != _prevAnimatedD) {
		_jugador->animate();
		_prevAnimatedD = _ellapsedTimeD;
		for (int i = 0; i < _playerBullets.size(); ++i) {
			_playerBullets[i]->animate();
		}
		for (int i = 0; i < _aliens.size(); ++i) {
			_aliens[i]->animate();
		}
		for (int i = 0; i < _alienBullets.size(); ++i) {
			_alienBullets[i]->animate();
		}
	}
	if (_ellapsedTimeD % 3 == 0 && _ellapsedTimeD != _prevShootTime) {
		_shoot = false;
	}
	_jugador->update(0.02f, false);
	for (int i = 0; i < _playerBullets.size(); ++i) {
		_playerBullets[i]->update(0.02, false);
		if (_playerBullets[i]->getPosition().y > _window->getScreenHeight()) {
			PlayerBullet* b = _playerBullets[i];
			_playerBullets.erase(_playerBullets.begin() + i);
			delete b;
		}
	}
	for (int i = 0; i < _alienBullets.size(); ++i) {
		_alienBullets[i]->update(0.02, false);
		if (_alienBullets[i]->collideWithAgent(_jugador)) {
			if (_jugador->damage(_alienBullets[i]->_damage) && !_gameOver) {
				_gameOver = true;
				_currentState = ScreenState::CHANGE_NEXT;
			}
			AlienBullet *ab = _alienBullets[i];
			_alienBullets.erase(_alienBullets.begin() + i);
			delete ab;
		}
	}
	for (int i = 0; i < _aliens.size(); ++i) {
		_aliens[i]->update(0.02, false, _window->getScreenWidth());
		if (_aliens[i]->canShoot()) {
			_alienBullets.push_back(new AlienBullet(20, 50,
				glm::vec2(_aliens[i]->getPosition().x + _aliens[i]->getWidth() / 2.0f,
					_aliens[i]->getPosition().y), _aliens[i]->_bulletType, 2));
			_aliens[i]->_timeToShoot = 0;
		}
		for (int j = 0; j < _playerBullets.size(); ++j) {
			if (_playerBullets[j]->collideWithAgent(_aliens[i])) {
				if (_aliens[i]->damaged(300)) {
					Alien* a = _aliens[i];
					_aliens.erase(_aliens.begin() + i);
					delete a;
					_points += 200;
				}
				PlayerBullet* pb = _playerBullets[j];
				_playerBullets.erase(_playerBullets.begin() + j);
				delete pb;
			}
		}
	}
	checkInput();
	if (_game->_inputManager.isKeyDown(SDLK_SPACE) && !_shoot) {
		_playerBullets.push_back(new PlayerBullet(20, 50, 
			glm::vec2(_jugador->getPosition().x + _jugador->getWidth() / 2.0f,
				_jugador->getPosition().y), 2));
		_shoot = true;
		_prevShootTime = _ellapsedTimeD;
	}
}

void PlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void PlayScreen::initRound() {
	_jugador = new Player(
		80, 50,
		glm::vec2(_window->getScreenWidth() / 2.0f, 0),
		&_game->_inputManager, 3);
	_beginTime = clock();
	if (_roundNumber == 1) {
		for (int i = 0; i < 12; ++i) {
			float x = rand() % (_window->getScreenWidth() - 61);
			int row = rand() % 3;
			float y = row * 80;
			_aliens.push_back(new Alien(60, 80,
				glm::vec2(x + 1, _window->getScreenHeight() - y - 80), rand() % 4, rand() % 4,
				rand() % 4, rand() % 4, rand() % 4, 3));
		}
	}
}

void PlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();
	_background->draw(_spriteBatch);
	_jugador->draw(_spriteBatch);
	for (int i = 0; i < _playerBullets.size(); ++i) {
		_playerBullets[i]->draw(_spriteBatch);
	}
	for (int i = 0; i < _aliens.size(); ++i) {
		_aliens[i]->draw(_spriteBatch);
	}
	for (int i = 0; i < _alienBullets.size(); ++i) {
		_alienBullets[i]->draw(_spriteBatch);
	}
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void PlayScreen::drawHUD() {
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	_hudBach.begin();
	std::string timeMessage = "TIEMPO: " + std::to_string(_ellapsedTimeI);
	sprintf_s(buffer, timeMessage.c_str());
	_spriteFont->draw(_hudBach, buffer, glm::vec2(0, 0),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 0, 255)
	);
	std::string pointsMessage = "PUNTAJE: " + std::to_string(_points);
	sprintf_s(buffer, pointsMessage.c_str());
	_spriteFont->draw(_hudBach, buffer, glm::vec2(_window->getScreenWidth() - 150, 0),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 0, 255));
	std::string lifeMessage = "VIDA: " + std::to_string((int)_jugador->getLife());
	sprintf_s(buffer, lifeMessage.c_str());
	_spriteFont->draw(_hudBach, buffer, glm::vec2(_window->getScreenWidth() / 2 - 50, 0),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 0, 255));
	_hudBach.end();
	_hudBach.renderBatch();
}

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	return SCREEN_INDEX_OVER;
}
