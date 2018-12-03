#include "Helpers.h"
#include <cmath>

Helpers::Helpers()
{
}

std::vector<std::bitset<NBITS>> Helpers::values(std::vector<Alien*> aliens) {
	std::vector<std::bitset<NBITS>> values;
	for (int i = 0; i < aliens.size(); ++i) {
		std::string string_bits = "";
		string_bits += std::bitset<2>(aliens[i]->_armorType).to_string();
		string_bits += std::bitset<2>(aliens[i]->_shieldType).to_string();
		string_bits += std::bitset<2>(aliens[i]->_motorType).to_string();
		string_bits += std::bitset<2>(aliens[i]->_canonType).to_string();
		string_bits += std::bitset<2>(aliens[i]->_bulletType).to_string();
		values.push_back(std::bitset<NBITS>(string_bits));
	}
	return values;
}

std::vector<int> Helpers::fitness(std::vector<Alien*> aliens) {
	std::vector<int> fitness;
	for (int i = 0; i < aliens.size(); ++i) {
		fitness.push_back(aliens[i]->_timeLived);
	}
	return fitness;
}

std::vector<Alien*> Helpers::generateAliens(std::vector<std::bitset<NBITS>> values, 
	int nAliens, int width, int height, int maxWidth, int maxHeight) {
	std::vector<Alien*> aliens;
	for (int i = 0; i < nAliens; ++i) {
		float x = rand() % (maxWidth - 61);
		int row = rand() % 3;
		float y = row * 80;
		std::string string_bites = values[i].to_string();
		int armorType = stringBitsToInt(string_bites.substr(0, 2));
		int shieldType = stringBitsToInt(string_bites.substr(2, 2));
		int motorType = stringBitsToInt(string_bites.substr(4, 2));
		int canonType = stringBitsToInt(string_bites.substr(6, 2));
		int bulletType = stringBitsToInt(string_bites.substr(8, 2));
  		aliens.push_back(new Alien(width, height,
			glm::vec2(x + 1, maxHeight - y - 80), armorType, bulletType,
			shieldType, motorType, canonType, 3));
	}
	return aliens;
}

int Helpers::stringBitsToInt(std::string stringBits) {
	int result = 0;
	for (int i = 0; i < stringBits.size(); ++i) {
		int number = stringBits[i] - 48;
		result += number * (int)pow(2, stringBits.size() - (i + 1));
	}
	return result;
}

Helpers::~Helpers()
{
}
