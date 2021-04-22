#include <fstream>
#include "Consumer.h"

void Consumer::ProcessData() {
	while (!Queue::s_creationProcessFinished || _queuePointer->GetQueueReference().size() > 0) {
		if (_queuePointer->GetQueueReference().size() == 0)
			std::this_thread::yield();
		else {
			if (_queuePointer->GetQueueStatus().first) {
				std::array<int, 100000> processingElement = _queuePointer->PopFirstElement();
				std::sort(processingElement.begin(), processingElement.end());
				_sortedProducts++;
				int accumulation = std::accumulate(processingElement.begin(), processingElement.end(), 0);				
				_summedValues.emplace_back(accumulation);
			}
		}
	}
}

void Consumer::GenerateReport() const {
	std::ofstream outFile("Processing_Report.csv", std::ofstream::out | std::ofstream::app);
	outFile << "Consumer id: " << _consumerThread.get_id() << ":\n";
	outFile << "Sorted products: " << _sortedProducts << "\nAcquired sums:\n";
	for (auto& it : _summedValues) {
		outFile << "	" << it << "\n";
	}
	outFile << "<------------------------------------------------------------------->\n";
}
