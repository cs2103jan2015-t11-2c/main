#include <fstream>
#include <string>
using namespace std;
#pragma once

class Log
{
private:
	ofstream file;

public:
	Log(void);
	~Log(void);

	void clear();
	void log(string);
	void endLog();
};

