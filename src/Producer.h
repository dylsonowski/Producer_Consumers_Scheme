#pragma once
#include <list>
#include <array>
#include <memory>
#include <thread>

class Producer {

public:
	Producer() = delete;
	Producer(std::shared_ptr<std::list<std::array<int, 100000>>> queuePointer, unsigned int queueSize);
	~Producer() = default;

private:
	std::thread::id _threadId;
	std::shared_ptr<std::list<std::array<int, 100000>>> _queuePointer;
	unsigned int _queueSize;
};

