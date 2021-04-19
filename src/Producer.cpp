#include "Producer.h"

int Producer::GenerateRandomNumber(int lowerRange, int upperRange) {
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> uniformDist(lowerRange, upperRange);
	return uniformDist(engine);
}

void Producer::StartProduction() {
	while (!_queuePointer->empty()) {
		std::this_thread::yield();
	}

	for (unsigned int listIt = 0; listIt < _queueSize; listIt++) {
		std::array<int, 100000> temp;
		for (auto& arrayIt : temp) {
			arrayIt = GenerateRandomNumber(-1000, 1000);
		}
		_queuePointer->emplace_back(temp);
	}
}
