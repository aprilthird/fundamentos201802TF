#pragma once
#include "Agent.h"
#include "InputManager.h"

const float PLAYER_SPEED = 8.0f;
const float PLAYER_LIFE = 10;

class Player : public Agent
{
private:
	InputManager* _inputManager;
	char _direction;
	float _life;
public:
	Player(float agent_width,
		float agent_height,
		glm::vec2 position,
		int maxSpritesNumber = 0
	);
	Player(float agent_width,
			float agent_height,
			glm::vec2 position,
			std::string texture,
			int maxSpritesNumber = 0
	);
	Player(float agent_width,
		float agent_height,
		glm::vec2 position,
		InputManager* inputManager,
		int maxSpritesNumber = 0
	);
	Player(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture,
		InputManager* inputManager,
		int maxSpritesNumber = 0
	);
	void update(float deltaTime,bool reloj);
	void setPosition(glm::vec2 position);
	bool damage(float damage);
	void changeTexture(std::string texturePath);
	std::string getTexture();
	void buildTexturePath();
	float getLife() const {
		return _life;
	}
	~Player();
};

