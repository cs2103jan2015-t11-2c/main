#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <windows.h>


class Entry {
public:
	std::string subject;
	int day;
	int month;
	int year;
	int startTime;
	int endTime;
	std::string priority;
	std::string category;
	bool completed;
	bool floating;
};

#endif