#include <fstream>
#include "Consumer.h"

void Consumer::ProcessData() {
	while (_queuePointer->empty()) {
		std::this_thread::yield();
	}

	while (!_queuePointer->empty()) {
		const std::lock_guard<std::mutex> guardian(s_readBlock);
		std::sort(_queuePointer->front().begin(), _queuePointer->front().end());
		_sortedProducts++;
		int accumulation = 0;
		std::accumulate(_queuePointer->front().begin(), _queuePointer->front().end(), accumulation);
		_summedValues.emplace_back(accumulation);
		_queuePointer->pop_front();
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
