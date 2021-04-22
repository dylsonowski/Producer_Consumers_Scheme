#include "Queue.h"

std::mutex Queue::s_queueBlock;
bool Queue::s_creationProcessFinished = false;

void Queue::ChangeQueueStatus(bool canRead, bool canWrite) {
	_canRead = canRead;
	_canWrite = canWrite;
}

bool Queue::AddElement(std::array<int, 100000> newElement) {
	if (_canWrite) {
		s_queueBlock.lock();
		_taskQueue.emplace_back(newElement);
		s_queueBlock.unlock();
		return true;
	}
	else
		return false;
}

std::array<int, 100000> Queue::PopFirstElement() {
	if (_canRead) {
		s_queueBlock.lock();
		std::array<int, 100000> temp = _taskQueue.front();
		_taskQueue.pop_front();
		s_queueBlock.unlock();
		return temp;
	}
}
