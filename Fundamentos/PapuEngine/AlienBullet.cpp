#include "AlienBullet.h"
#include "Constants.h"
#include "SpaceShipParts.h"


AlienBullet::AlienBullet(float agent_width,
	float agent_height,
	glm::vec2 position,
	int type,
	int maxSpritesNumber) :
	Agent(agent_width, agent_height, position, maxSpritesNumber)
{
	_type = type;
	_damage = BULLET::VALUES[_type]->damage;
	_speed = BULLET::VALUES[_type]->speed;
	_spriteNumber = 0;
	buildTexturePath();
}

void AlienBullet::update(float deltaTime, bool reloj) {
	_position.y -= _speed;
	buildTexturePath();
}

void AlienBullet::setPosition(glm::vec2 position) {
	_position = position;
}

void AlienBullet::changeTexture(std::string texturePath) {
	_texturePath = texturePath;
}

std::string AlienBullet::getTexture() {
	return _texturePath;
}

void AlienBullet::buildTexturePath() {
	_texturePath = PATH::SPRITES + "/"
		+ std::to_string(_spriteNumber) + "_"
		+ PATH::SPRITES_NAMES::ALIEN_BULLET + "_"
		+ BULLET::VALUES[_type]->abvr + ".png";
}

AlienBullet::~AlienBullet()
{
}
