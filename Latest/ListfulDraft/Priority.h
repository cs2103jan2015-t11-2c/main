#ifndef PRIORITY_H
#define PRIORITY_H

#include "DataStore.h"

class Priority {
	private:
		std::string _priority;

	public:
		Priority() {};

		bool extractPriority(int, std::string &, size_t);
		
		void updateStr(std::string &, size_t);

		std::string &getPriority();
};

#endif