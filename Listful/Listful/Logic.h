#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>


class Logic {
public:
	Logic(void);
	void printContent(std::string &);
	void addContent(std::string &, std::string);
	bool isDuplicate(std::string &);
	void deleteContent(std::string &);
	void clearFile(std::string &);
	void compareLineSize(std::string &, std::string &, std::string &);
	bool compareWord(std::string &, std::string &, std::string &);
	void sortFile(std::string);
	void switchPlaces(int &, int &);
	void searchFile(std::string &, std::string);
	bool foundContent(std::string &);
	~Logic(void);
};

#endif