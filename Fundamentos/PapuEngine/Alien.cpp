#include "Alien.h"
#include "SpaceShipParts.h"
#include "Constants.h"
#include "ResourceManager.h"

Alien::Alien(float agent_width,
	float agent_height,
	glm::vec2 position,
	int armorType,
	int bulletType,
	int shieldType,
	int motorType,
	int canonType,
	int maxSpritesNumber) :
	Agent(agent_width, agent_height, position, maxSpritesNumber)
{
	_armorType = armorType;
	_bulletType = bulletType;
	_shieldType = shieldType;
	_motorType = motorType;
	_canonType = canonType;
	_armorDuration = ARMOR::VALUES[_armorType]->duration;
	_shieldDuration = SHIELD::VALUES[_shieldType]->duration;
	_speed = MOTOR::VALUES[_motorType]->speed;
	_timeLived = 0;
	_spriteNumber = 0;
	_direction = 1;
	_timeToShoot = 0;
}

void Alien::draw(SpriteBacth& spriteBatch) {
	std::string shipPath = buildShipPath();
	std::string canonPath = buildCanonPath();
	std::string motorPath = buildMotorPath();
	
	int shipTextureId = ResourceManager::getTexture(shipPath).id;
	int canonTextureId = ResourceManager::getTexture(canonPath).id;
	int motorTextureId = ResourceManager::getTexture(motorPath).id;
	int shieldTextureId = ResourceManager::getTexture(PATH::SPRITES_NAMES::SHIELD).id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA  color;
	color.set(255, 255, 255, 255);
	glm::vec4 destRect(_position.x, _position.y, _agent_width, _agent_height);
	spriteBatch.draw(destRect, uvRect, shipTextureId, 0.0f, color);

	int nMotors = MOTOR::VALUES[_motorType]->nmotors;
	for (int i = 0; i < nMotors; ++i) {
		glm::vec4 drMotor(_position.x + ((_agent_width / (nMotors + 1)) * i), _position.y + _agent_height / 3, 20, 50);
		spriteBatch.draw(drMotor, uvRect, motorTextureId, 0.0f, color);
	}

	int nCanons = CANON::VALUES[_canonType]->ncanons;
	for (int i = 0; i < nCanons; ++i) {
		glm::vec4 drCanon(_position.x, _position.y + ((_agent_height / (nCanons + 1))* i), _agent_width, _agent_height / 4);
		spriteBatch.draw(drCanon, uvRect, canonTextureId, 0.0f, color);
	}

	if (_shieldType != SHIELD::NONE && _shieldDuration > 0) {
		glm::vec4 destRectShield(_position.x - 10, _position.y + 10, _agent_width + 20, _agent_height + 20);
		spriteBatch.draw(destRectShield, uvRect, shieldTextureId, 0.0f, SHIELD::VALUES[_shieldType]->color);
	}
}

void Alien::update(float deltaTime, bool reloj) {
}

void Alien::update(float deltaTime, bool reloj, int maxWidth) {
	if (_position.x < 0 || _position.x + _agent_width > maxWidth)
		_direction *= -1;
	_position.x += _speed * _direction;
	_timeLived++;
	_timeToShoot++;
}

bool Alien::canShoot() {
	return _timeToShoot > CANON::VALUES[_canonType]->time;
}

bool Alien::damaged(float damage) {
	if (_shieldDuration > 0) {
		_shieldDuration -= damage;
	}
	else {
		_armorDuration -= (damage * (1.0f - ARMOR::VALUES[_armorType]->protection));
	}
	return _armorDuration < 0;
}

void Alien::setPosition(glm::vec2 position) {
	_position = position;
}
void Alien::changeTexture(std::string texturePath) {
	_texturePath = texturePath;
}
std::string Alien::getTexture() {
	return _texturePath;
}
std::string Alien::buildShipPath() {
	return PATH::SPRITES + "/"
		+ std::to_string(_spriteNumber) + "_"
		+ PATH::SPRITES_NAMES::ALIEN_SPACHESHIP + "_"
		+ ARMOR::VALUES[_armorType]->abvr + ".png";
}

std::string Alien::buildCanonPath() {
	return PATH::SPRITES + "/"
		+ std::to_string(_spriteNumber) + "_"
		+ PATH::SPRITES_NAMES::ALIEN_CANON + "_"
		+ ARMOR::VALUES[_armorType]->abvr + ".png";
}

std::string Alien::buildMotorPath() {
	return PATH::SPRITES + "/"
		+ std::to_string(_spriteNumber) + "_"
		+ PATH::SPRITES_NAMES::ALIEN_MOTOR + "_"
		+ ARMOR::VALUES[_armorType]->abvr + ".png";
}

Alien::~Alien()
{
}
