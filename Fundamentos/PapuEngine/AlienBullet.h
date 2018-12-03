#pragma once
#include "Agent.h"

class AlienBullet : public Agent
{
public:
	int _type;
	float _damage;
	AlienBullet(float agent_width,
		float agent_height,
		glm::vec2 position,
		int type,
		int maxSpritesNumber = 0);
	void update(float deltaTime, bool reloj);
	void setPosition(glm::vec2 position);
	void changeTexture(std::string texturePath);
	std::string getTexture();
	void buildTexturePath();
	~AlienBullet();
};

