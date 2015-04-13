#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <iostream>

class Log {
private:
	std::string _logFileName;
//	std::ofstream file;

public:
	Log() {};

	void clear();
	void log(std::string);
	void endLog();
	std::string &get_logFileName();
};

#endif