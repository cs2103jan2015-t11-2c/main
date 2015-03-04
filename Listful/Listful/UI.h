#ifndef UI_H
#define UI_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>

//Command messages
static const std::string MESSAGE_ADD;
static const std::string MESSAGE_DELETE;
static const std::string MESSAGE_CLEAR;
static const std::string MESSAGE_EMPTY;
static const std::string MESSAGE_SORT;

//Welcome message
static const std::string MESSAGE_WELCOME;

//Error messages
static const std::string ERROR_COMMAND;
static const std::string ERROR_DELETE;
static const std::string ERROR_ADD;
static const std::string ERROR_SEARCH;

//Index of created text file name
static const int FILE_INDEX;

class UI {
public:
	UI(void);
	~UI(void);
};

#endif