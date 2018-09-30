#pragma once
#include "Entity.h"

class Zombie : public Entity
{
public:
	Zombie();
	void init(float speedd, glm::vec2 position);
	void update(const std::vector<std::string>&levelData,
		std::vector<Zombie*>& humans,
		std::vector<Zombie*>& zombies
		);
	~Zombie();
};

