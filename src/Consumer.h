#pragma once
#include <algorithm>
#include <numeric>
#include <list>
#include <array>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>

class Consumer {

public:
	Consumer() = delete;
	Consumer(std::shared_ptr<std::list<std::array<int, 100000>>> queuePointer) : _queuePointer(queuePointer) {
		_consumerThread = std::thread(&Consumer::ProcessData, this);
	}
	~Consumer() { GenerateReport(); _consumerThread.join(); }

private:
	void ProcessData();
	void GenerateReport() const;

	std::thread _consumerThread;
	std::shared_ptr<std::list<std::array<int, 100000>>> _queuePointer;
	static std::mutex s_readBlock;
	std::vector<int> _summedValues;
	unsigned int _sortedProducts;
};

