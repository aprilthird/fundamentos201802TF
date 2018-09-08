#pragma once
#include <map>
#include "GLTexture.h";

using namespace std;

class TextureCache
{
	map<string, GLTexture> textureMap;
public:
	TextureCache();
	~TextureCache();
	GLTexture getTexture(string texturePath);
};

