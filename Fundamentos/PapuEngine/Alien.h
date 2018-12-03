#pragma once
#include "Agent.h"

class Alien : public Agent
{
public:
	float _shieldDuration;
	float _armorDuration;
	float _timeLived;
	int _armorType;
	int _bulletType;
	int _motorType;
	int _shieldType;
	int _canonType;
	int _direction;
	int _timeToShoot;
	Alien(float agent_width,
		float agent_height,
		glm::vec2 position,
		int armorType,
		int bulletType,
		int shieldType,
		int motorType,
		int canonType,
		int maxSpritesNumber = 0);
	void update(float deltaTime, bool reloj);
	void update(float deltaTime, bool reloj, int maxWidth);
	void setPosition(glm::vec2 position);
	void changeTexture(std::string texturePath);
	bool damaged(float damage);
	std::string getTexture();
	std::string buildShipPath();
	std::string buildMotorPath();
	std::string buildCanonPath();
	void draw(SpriteBacth& spriteBatch);
	bool canShoot();
	~Alien();
};

