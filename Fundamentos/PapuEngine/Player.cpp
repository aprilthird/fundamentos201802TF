#include "Player.h"
#include <SDL\SDL.h>
#include <iostream>
#include "Constants.h"

Player::Player(float agent_width,
	float agent_height,
	glm::vec2 position,
	int maxSpritesNumber) :
	Agent(agent_width, agent_height, position, maxSpritesNumber)
{
	_speed = PLAYER_SPEED;
	_direction = 'Q';
	buildTexturePath();
	_life = PLAYER_LIFE;
}

Player::Player(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	int maxSpritesNumber):
		Agent(agent_width,agent_height,position,texture,maxSpritesNumber)
{
	_speed = PLAYER_SPEED;
	_direction = 'Q';
	buildTexturePath();
	_life = PLAYER_LIFE;
}

Player::Player(float agent_width,
	float agent_height,
	glm::vec2 position,
	InputManager* inputManager,
	int maxSpritesNumber
) :
	Agent(agent_width, agent_height, position, maxSpritesNumber)
{
	_speed = PLAYER_SPEED;
	_inputManager = inputManager;
	_direction = 'Q';
	buildTexturePath();
	_life = PLAYER_LIFE;
}

Player::Player(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	InputManager* inputManager, 
	int maxSpritesNumber
	) :
	Agent(agent_width, agent_height, position, texture, maxSpritesNumber)
{
	_speed = PLAYER_SPEED;
	_inputManager = inputManager;
	_direction = 'Q';
	buildTexturePath();
	_life = PLAYER_LIFE;
}

void Player::update(float deltaTime,bool reloj) {
	bool pressKey = false;
	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += _speed;
		pressKey = true;
	}
	if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= _speed;
		pressKey = true;
	}
	if (_inputManager->isKeyDown(SDLK_a)) {
		_position.x -= _speed;
		_direction = 'I';
		pressKey = true;
	}
	else if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += _speed;
		_direction = 'D';
		pressKey = true;
	}
	else {
		_direction = 'Q';
	}
	buildTexturePath();
}

bool Player::damage(float damage) {
	_life -= damage;
	return _life < 0;
}

void Player::setPosition(glm::vec2 position) {
	_position = position;
}
void Player::changeTexture(std::string texturePath) {
	_texturePath = texturePath;
}
std::string Player::getTexture() {
	return _texturePath;
}
void Player::buildTexturePath() {
	_texturePath = PATH::SPRITES + "/"
		+ std::to_string(_spriteNumber) + "_"
		+ PATH::SPRITES_NAMES::PLAYER + "_"
		+ _direction + ".png";
}
Player::~Player()
{
}
