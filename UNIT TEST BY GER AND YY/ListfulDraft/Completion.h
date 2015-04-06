#ifndef COmpletION_H
#define COMPLETION_H

#include "DataStore.h"

class Completion {
public:
	Completion() {};

	void updateCompleted(DataStore &, int);
	bool checkCompleted(DataStore &, int);
};

#endif