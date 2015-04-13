//@author A0115871E
#ifndef PRIORITY_H
#define PRIORITY_H

#include "DataStore.h"

class Priority {
	private:
		std::string _priority;

	public:
		Priority() {};

		bool checkForPriority(int, std::string &, size_t);
		
		void extractRemainingStr(std::string &, size_t);

		std::string &getPriority();
};

#endif