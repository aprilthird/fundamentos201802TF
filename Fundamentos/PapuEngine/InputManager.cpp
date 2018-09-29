#include "InputManager.h"



InputManager::InputManager():mouseCoords(0.0,0.0)
{
}


InputManager::~InputManager()
{
}


void InputManager::setMouseCoords(float x, float y){
	mouseCoords.x = x;
	mouseCoords.y = y;

}
void InputManager::pressKey(unsigned int keyCode) {
	keys[keyCode] = true;
}
void InputManager::releaseKey(unsigned int keyCode) {
	keys[keyCode] = false;
}


void InputManager::update() {
	for (auto& it: keys) {
		previuosKey[it.first] = it.second;
	}
}

bool InputManager::isKeyPressed(unsigned int keyCode) {
	if (isKeyDown(keyCode) && !wasKeyDown(keyCode)) {
		return true;
	}
	return false;
}

bool InputManager::isKeyDown(unsigned int keyCode) {
	auto it = keys.find(keyCode);
	if (it != keys.end()) {
		return it->second;
	}
}

bool InputManager::wasKeyDown(unsigned int keyCode) {
	auto it = previuosKey.find(keyCode);
	if (it != previuosKey.end()) {
		return it->second;
	}
}
