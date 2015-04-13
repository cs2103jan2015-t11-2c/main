#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <iostream>

#pragma once

class Log
{
private:
	std::ofstream file;

public:
	Log(void);
	~Log(void);

	void clear();
	void log(std::string);
	void endLog();
};

#endif