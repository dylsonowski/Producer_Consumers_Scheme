#include <iostream>
#include "Producer.h"

class Queue;
int main(int argc, char** argv) {


	system("pause");
	return 0;
}

class Queue {

public:
	Queue() = delete;
	Queue(unsigned int queueSize) : _queueSize(queueSize) {}
	~Queue() = default;

	inline unsigned int GetQueueSize() const { return _queueSize; }
	inline std::shared_ptr<std::list<std::array<int, 100000>>> GetQueuePointer() const { return std::make_shared<std::list<std::array<int, 100000>>>(_taskQueue); }
	inline std::thread::id GetThreadId() const { return _threadId; }

private:
	std::thread::id _threadId;
	unsigned int _queueSize;
	std::list<std::array<int, 100000>> _taskQueue;
};