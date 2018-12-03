#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
}

std::vector<std::bitset<NBITS>> GeneticAlgorithm::deleteWorst(
	std::vector<std::bitset<NBITS>> values, std::vector<int> fitness) {
	int bestFitness = 0, worstFitness = 0;
	for (int i = 0; i < fitness.size() - 1; ++i) {
		if (fitness[i] > fitness[i + 1])
			bestFitness = i;
		if (fitness[i] < fitness[i + 1])
			worstFitness = i;
	}
	values[worstFitness] = values[bestFitness];
	return values;
}

std::vector<std::bitset<NBITS>> GeneticAlgorithm::makePairs(
	std::vector<std::bitset<NBITS>> values) {
	for (int i = 0; i < values.size() / 2; ++i) {
		int randPosI = rand() % (values.size() / 2);
		int randPosD = (rand() % values.size() / 2) + (values.size() / 2);
		std::bitset<NBITS> orig = values[randPosI];
		std::bitset<NBITS> dest = values[randPosD];
		values[randPosI] = dest;
		values[randPosD] = orig;
	}
	return values;
}

std::vector<std::bitset<NBITS>> GeneticAlgorithm::crossover(
	std::vector<std::bitset<NBITS>> values) {
	for (int i = 0; i < values.size() / 2; i++) {
		int crossoverPoint = rand() % NBITS;
		std::bitset<NBITS> pair1 = values[i * 2];
		std::bitset<NBITS> pair2 = values[(i * 2) + 1];
		for (int j = 0; j < crossoverPoint; ++j) {
			pair1[j] = pair2[j];
		}
		for (int j = crossoverPoint; j < NBITS; ++j) {
			pair2[j] = pair1[j];
		}
		values[i] = pair1;
		values[(i * 2) + 1] = pair2;
	}
	return values;
}

std::vector<std::bitset<NBITS>> GeneticAlgorithm::mutation(
	std::vector<std::bitset<NBITS>> values) {
	for (int i = 0; i < values.size(); i++) {
		int mutationProb = rand() % 100;
		if (mutationProb > 20 && mutationProb < 30) { // 10% probabilidad de mutación
			int mutIndex = rand() % NBITS;
			values[i][mutIndex] = values[i][mutIndex] == 0 ? 1 : 0;
		}
	}
	return values;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}
