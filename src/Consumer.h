#pragma once
#include <algorithm>
#include <numeric>
#include <list>
#include <array>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include "Queue.h"

class Consumer {

public:
	Consumer() = delete;
	Consumer(std::shared_ptr<Queue> queuePointer) : _queuePointer(queuePointer) {
		_consumerThread = std::thread(&Consumer::ProcessData, this);
	}
	~Consumer() { GenerateReport(); _consumerThread.join(); }

private:
	void ProcessData();
	void GenerateReport() const;

	std::thread _consumerThread;
	std::shared_ptr<Queue> _queuePointer;
	std::vector<int> _summedValues;
	unsigned int _sortedProducts;
};

