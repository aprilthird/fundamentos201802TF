#pragma once
#include "Alien.h"
#include <vector>
#include <bitset>
#include "GeneticAlgorithm.h"

class Helpers
{
public:
	Helpers();
	static std::vector<std::bitset<NBITS>> values(std::vector<Alien*> aliens);
	static std::vector<int> fitness(std::vector<Alien*> aliens);
	static std::vector<Alien*> generateAliens(std::vector<std::bitset<NBITS>> values, 
		int nAliens, int width, int height, int maxWidth, int maxHeight);
	static int stringBitsToInt(std::string stringBits);
	~Helpers();
};

