#include "PlayerBullet.h"
#include "Constants.h"


PlayerBullet::PlayerBullet(float agent_width,
	float agent_height,
	glm::vec2 position,
	int maxSpritesNumber) : 
	Agent(agent_width, agent_height, position, maxSpritesNumber)
{
	_speed = PLAYER_BULLET_SPEED;
	buildTexturePath();
}

void PlayerBullet::update(float deltaTime, bool reloj) {
	_position.y += _speed;
	buildTexturePath();
}

void PlayerBullet::setPosition(glm::vec2 position) {
	_position = position;
}

void PlayerBullet::changeTexture(std::string texturePath) {
	_texturePath = texturePath;
}

std::string PlayerBullet::getTexture() {
	return _texturePath;
}

void PlayerBullet::buildTexturePath() {
	_texturePath = PATH::SPRITES + "/"
		+ std::to_string(_spriteNumber) + "_"
		+ PATH::SPRITES_NAMES::PLAYER_BULLET + ".png";
}

PlayerBullet::~PlayerBullet()
{
}
