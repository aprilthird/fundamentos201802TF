#pragma once
#include "SpriteBacth.h"
#include <glm\glm.hpp>;
#include "GLTexture.h";
#include <string>;

class Button
{
private:
	std::string _texture;
	int _textureID;
	glm::vec2 _position;
	std::string _text;
public:
	Button(std::string texture, glm::vec2 position, std::string text);
	void draw(SpriteBacth& spriteBatch);
	bool clicked(glm::vec2 position);
	void setPosition(glm::vec2 position);
	glm::vec2 getPosition() const {
		return _position;
	}
	std::string getText() const {
		return _text;
	}
	~Button();
};

