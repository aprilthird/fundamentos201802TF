#include "Background.h"
#include "ResourceManager.h";


Background::Background(std::string texture, float width, float height)
			:_texture(texture), _width(width), _height(height)
{
	_textureID 
		= ResourceManager::getTexture(_texture).id;
	_color.set(255, 255, 255, 255);
}

void Background::draw(SpriteBacth& spriteBatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desctRect(0, 0, _width, _height);
	spriteBatch.draw(desctRect, uvRect, _textureID, 0.0f, _color);
}

void Background::setColor(ColorRGBA color) {
	_color = color;
}


Background::~Background()
{
}
