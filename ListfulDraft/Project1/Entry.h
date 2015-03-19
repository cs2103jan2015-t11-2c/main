#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <assert.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>

class Entry {
public:
	std::string subject;
	int day;
	int month;
	int year;
	int startTime;
	int endTime;
	std::string impt;
	std::string category;
};

#endif