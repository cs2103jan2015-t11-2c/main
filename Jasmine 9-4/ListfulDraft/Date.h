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
	void changeToLower(std::string &);
	void removeNonDateChar(std::string &);
	bool extractNum(std::string, int &, int &);
	void removeExtraLetters(std::string, int &);
	bool dateInLetter(std::string &);
	bool takeDay(std::string&, size_t &);
	bool takeMonth(std::string&, size_t &, size_t &);
	void takeYear(std::string &, std::string, std::string, size_t);
	bool isDayMonth(bool &);
	bool extractDate(std::string &, bool &, std::string, size_t, bool);

	int &getDay();
	int &getMonth();
	int &getYear();
};

#endif