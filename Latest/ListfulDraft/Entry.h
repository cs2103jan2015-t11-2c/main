//@author A0110670W
#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <wchar.h>

class Entry {
	public:
		int referenceNo;

		std::string subject;
		int day;
		int month;
		int year;
		int startTime;
		int endTime;
		std::string priority;
		std::string category;
		bool isTimedTask;
		bool isComplete;
		bool isFloat;
};

#endif