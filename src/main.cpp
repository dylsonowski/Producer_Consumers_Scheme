#include <iostream>
#include "Producer.h"
#include "Consumer.h"

class Queue;
int main(int argc, char** argv) {
	std::unique_ptr<Queue> newQueue = std::make_unique<Queue>(100);
	std::vector<std::unique_ptr<Consumer>> consumers;
	for (unsigned int it = 0; it < 4; it++) {
		consumers.emplace_back(std::make_unique<Consumer>(newQueue->GetQueuePointer()));
	}

	system("pause");
	return 0;
}

class Queue {

public:
	Queue() = delete;
	Queue(unsigned int queueSize, unsigned int numberToCreate) : _queueSize(queueSize) { 
		_queueStatus = std::make_pair(false, true); //(canRead, canWrite)
		_queueThread = std::thread(&Queue::CreateTaskQueue, this, numberToCreate);
	}
	~Queue() { _queueThread.join(); }

	void AddElement(std::array<int, 100000> newElement) {
		if (_queueStatus.second) {
			_queueStatus.first = false;
			s_queueBlock.lock();
			_taskQueue.emplace_back(newElement);
			s_queueBlock.unlock();
			_queueStatus.first = true;
		}
	}
	
	inline unsigned int GetQueueSize() const { return _queueSize; }
	inline std::shared_ptr<std::list<std::array<int, 100000>>> GetQueuePointer() const { return std::make_shared<std::list<std::array<int, 100000>>>(_taskQueue); }
	inline std::array<int, 100000> PopFirstElement() {
		if (_queueStatus.first) {
			_queueStatus.second = false;
			s_queueBlock.lock();
			std::array<int, 100000> temp = _taskQueue.front();
			_taskQueue.pop_front();
			s_queueBlock.unlock();
			_queueStatus.second = true;
			return temp;
		}
	}

	static std::mutex s_queueBlock;
	static std::pair<bool, bool> _queueStatus;

private:
	void CreateTaskQueue(unsigned int numberToCreate) {
		Producer newProducer(std::make_shared<std::list<std::array<int, 100000>>>(_taskQueue), _queueSize, numberToCreate);
		while (!newProducer.GetCreationStatus()) {
			if (_taskQueue.empty()) {
				_queueStatus.first = false;
				_que
			}
			else
				_canWrite = true;
		}
	}

	std::thread _queueThread;
	unsigned int _queueSize;
	std::list<std::array<int, 100000>> _taskQueue;
};