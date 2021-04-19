#pragma once
#include <list>
#include <array>
#include <memory>
#include <thread>
#include <random>

class Producer {

public:
	Producer() = delete;
	Producer(std::shared_ptr<std::list<std::array<int, 100000>>> queuePointer, unsigned int queueSize) : _queuePointer(queuePointer), _queueSize(queueSize) {
		_producerThread = std::thread(&Producer::StartProduction, this);
	}
	~Producer() = default;

private:
	static int GenerateRandomNumber(int lowerRange, int upperRange);
	void StartProduction();

	std::thread _producerThread;
	std::shared_ptr<std::list<std::array<int, 100000>>> _queuePointer;
	unsigned int _queueSize;
};

