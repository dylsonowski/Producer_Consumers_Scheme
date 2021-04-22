#include <iostream>
#include <chrono>
#include "Producer.h"
#include "Consumer.h"
//#include "Queue.h"

using namespace std::literals::chrono_literals;

int main(int argc, char** argv) {
	std::shared_ptr<Queue> newQueue = std::make_shared<Queue>(100);
	std::unique_ptr<Producer> newProducer = std::make_unique<Producer>(newQueue, newQueue->GetQueueSize(), 500);
	std::vector<std::unique_ptr<Consumer>> consumers;
	for (unsigned int it = 0; it < 5; it++) {
		consumers.emplace_back(std::make_unique<Consumer>(newQueue));
	}

	while (!Queue::s_creationProcessFinished || newQueue->GetQueueReference().size() > 0) { 
		system("cls");
		std::cout << "Working...\n"; 
		std::this_thread::sleep_for(1s);
	}
	//std::cin.get();
	return 0;
}