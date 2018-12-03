#pragma once
#include "Agent.h"

const float PLAYER_BULLET_SPEED = 15.0f;

class PlayerBullet : public Agent
{
public:
	PlayerBullet(float agent_width,
		float agent_height,
		glm::vec2 position,
		int maxSpritesNumber = 0);
	void update(float deltaTime, bool reloj);
	void setPosition(glm::vec2 position);
	void changeTexture(std::string texturePath);
	std::string getTexture();
	void buildTexturePath();
	~PlayerBullet();
};

