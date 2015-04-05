#ifndef PRIORITY_H
#define PRIORITY_H

#include "DataStore.h"

class Priority {
private:
	std::string _priority;

public:
	Priority() {};

	bool extractPriority(std::string &);
	void updateStr(std::string &, size_t);
	void removeEndChar(std::string &);

	std::string &getPriority();
};

#endif