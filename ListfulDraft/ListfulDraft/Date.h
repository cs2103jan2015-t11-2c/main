#ifndef DATE_H
#define DATE_H

#include "DataStore.h"

class Date {
private:
	enum monthType {
		JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, INVALID
	};

	int _day;
	int _month;
	int _year;

public:
	Date() {};

	int determineMonth(std::string);
	bool extractNum(std::string &, size_t &, size_t &, int &, int &);
	void removeNonDateChar(std::string &);
	bool isDay(std::string&, size_t &, size_t &);
	bool isMonth(std::string&, size_t &, size_t &);
	bool isDayMonth();
	void isYear(std::string &, std::string &);
	bool extractDate(std::string &);
	void changeToLower(std::string &);

	int getDay();
	int getMonth();
	int getYear();
};

#endif