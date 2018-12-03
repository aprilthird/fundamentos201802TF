#pragma once
#include <vector>
#include <bitset>

const int NBITS = 10;

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	static std::vector<std::bitset<NBITS>> deleteWorst(
		std::vector<std::bitset<NBITS>> values, std::vector<int> fitness);
	static std::vector<std::bitset<NBITS>> makePairs(
		std::vector<std::bitset<NBITS>> values);
	static std::vector<std::bitset<NBITS>> crossover(
		std::vector<std::bitset<NBITS>> values);
	static std::vector<std::bitset<NBITS>> mutation(
		std::vector<std::bitset<NBITS>> values);
	~GeneticAlgorithm();
};

