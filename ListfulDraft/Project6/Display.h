#ifndef DISPLAY_H
#define DISPLAY_H

#include "DataStore.h"

class Display {
private:
	enum subDateCategory {
			DAY, MONTH, INVALID
	};

	int category;

public:
	Display() {};
	int determineCategory(std::string);
	void displayContent(std::string &, DataStore &, std::string, int);
};

#endif
