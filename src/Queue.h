#pragma once
#include <array>
#include <thread>
#include <mutex>
#include <list>

class Queue {

public:
	Queue() = delete;
	Queue(unsigned int queueSize) : _queueSize(queueSize), _canRead(false), _canWrite(true) {
		_queueThread = std::thread(&Queue::CreateTaskQueue, this);
	}
	~Queue() { _queueThread.join(); }

	void ChangeQueueStatus(bool canRead, bool canWrite);

	inline unsigned int GetQueueSize() const { return _queueSize; }
	bool AddElement(std::array<int, 100000> newElement);
	std::array<int, 100000> PopFirstElement();
	inline std::pair<bool, bool> GetQueueStatus() const { return std::make_pair(_canRead, _canWrite); }
	inline const std::list<std::array<int, 100000>>& GetQueueReference() const { return _taskQueue; }

	static std::mutex s_queueBlock;
	static bool s_creationProcessFinished;

private:
	void CreateTaskQueue() { while (!s_creationProcessFinished || _taskQueue.size() > 0); }

	std::thread _queueThread;
	unsigned int _queueSize;
	std::list<std::array<int, 100000>> _taskQueue;
	bool _canRead, _canWrite;
};