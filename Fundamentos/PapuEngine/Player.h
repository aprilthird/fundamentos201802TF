#pragma once
#include "Entity.h"
#include "InputManager.h"
#include <vector>
#include "Camera2D.h"

class Player : public Entity
{
private:
	InputManager* _inputManager;
	int _currentGun;
	Camera2D* _camera;
public:
	Player();
	~Player();
	void init(float speed, glm::vec2 position, 
				InputManager* inputManager,
				Camera2D* camera
		);
	void update(const std::vector<std::string>& levelData,
				std::vector<Player>& humans,
				std::vector<Player>& zombies
		);
};

