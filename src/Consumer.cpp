#include <fstream>
#include "Consumer.h"

void Consumer::ProcessData() {
	while (_queuePointer->empty()) {
		std::this_thread::yield();
	}

	while (!_queuePointer->empty()) {
		s_readBlock.lock();
		std::array<int, 100000> processingElement = _queuePointer->front();
		_queuePointer->pop_front();
		s_readBlock.unlock();

		std::sort(processingElement.begin(), processingElement.end());
		_sortedProducts++;
		int accumulation;
		std::accumulate(processingElement.begin(), processingElement.end(), accumulation);
		_summedValues.emplace_back(accumulation);
	}
}

void Consumer::GenerateReport() const {
	std::ofstream outFile("Processing_Report.csv", std::ofstream::out | std::ofstream::app);
	outFile << "Consumer id: " << std::this_thread::get_id << ":\n";
	outFile << "Sorted products: " << _sortedProducts << "\nAcquired sums:\n";
	for (auto& it : _summedValues) {
		outFile << "	" << it << "\n";
	}
	outFile << "<------------------------------------------------------------------->\n";
}
