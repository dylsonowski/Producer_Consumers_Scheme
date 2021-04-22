#include "Producer.h"

int Producer::GenerateRandomNumber(int lowerRange, int upperRange) {
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> uniformDist(lowerRange, upperRange);
	return uniformDist(engine);
}

void Producer::StartProduction() {
	while (_insertionCounter <= _numberToCreate) {
		if (_queuePointer->GetQueueReference().size() >= _queueSize) {
			while (_queuePointer->GetQueueReference().size() > 0) {
				_queuePointer->ChangeQueueStatus(true, false);
				std::this_thread::yield();
			}
		}
		else {
			_queuePointer->ChangeQueueStatus(false, true);
			if (_queuePointer->GetQueueReference().size() < _queueSize) {
				std::array<int, 100000> temp;
				for (auto& arrayIt : temp) {
					arrayIt = GenerateRandomNumber(-1000, 1000);
				}
				
				if (_queuePointer->AddElement(temp))
					_insertionCounter++;
			}
		}

		if (_insertionCounter == _numberToCreate)
			Queue::s_creationProcessFinished = true;
	}
}
