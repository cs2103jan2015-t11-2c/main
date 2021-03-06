//@author A0115871E-reused
#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <iostream>

class Log {
private:
	std::string _logFileName;

public:
	Log() {};

	void clear();
	void log(std::string);
	void endLog();
	std::string &get_logFileName();
};

#endif