#include "MenuScreen.h"
#include "MyScreens.h"
#include "Game.h"


MenuScreen::MenuScreen(Window* window):
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void MenuScreen::initGUI() {
	_spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
	_button = new Button("Textures/menu_button.png");
}

void MenuScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
							"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void MenuScreen::destroy() {
	delete _background;
	delete _button;
}

void MenuScreen::onExit() {}

void MenuScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(), 
					_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	_background = new Background("Textures/game.png");
	initGUI();
}

void MenuScreen::update() {
	_camera2D.update();
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		if (!btnGameClicked
			&& (_button->clicked(
				_game->_inputManager.getMouseCoords())))
		{
			btnGameClicked = true;
			_currentState = ScreenState::CHANGE_NEXT;
		}
	}
	checkInput();
}

void MenuScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void MenuScreen::draw() {
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
	_button->draw(_spriteBatch);
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	char buffer[256];
	_spriteBatch.begin();
	sprintf(buffer, " HOLA MI JUEGO");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(250, 100), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 255, 255));
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void MenuScreen::build() {}

int MenuScreen::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int MenuScreen::getNextScreen() const {
	return SCREEN_INDEX_GAME;
}

MenuScreen::~MenuScreen()
{
}
