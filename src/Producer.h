#pragma once
#include <list>
#include <array>
#include <memory>
#include <thread>
#include <random>
#include "Queue.h"

class Producer {

public:
	Producer() = delete;
	Producer(std::shared_ptr<Queue> queuePointer, unsigned int queueSize, unsigned int numberToCreate) 
		: _queuePointer(queuePointer), _queueSize(queueSize), _numberToCreate(numberToCreate), _creationFinished(false), _insertionCounter(0) {
		_producerThread = std::thread(&Producer::StartProduction, this);
	}
	~Producer() { _producerThread.join(); }

	//inline bool GetCreationStatus() const { return _creationFinished; }

private:
	static int GenerateRandomNumber(int lowerRange, int upperRange);
	void StartProduction();

	std::thread _producerThread;
	std::shared_ptr<Queue> _queuePointer;
	unsigned int _queueSize, _numberToCreate, _insertionCounter;
	bool _creationFinished;
};

