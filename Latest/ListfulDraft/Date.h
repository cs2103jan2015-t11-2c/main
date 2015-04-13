//@author A0115871E
#ifndef DATE_H
#define DATE_H

#include "DataStore.h"

class Date {
	private:
		enum monthType {
			JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, INVALIDMONTH
		};

		enum dayType {
			SUN, MON, TUE, WED, THUR, FRI, SAT, INVALIDDAY
		};

		int _day;
		int _month;
		int _year;

	public:
		Date() {};

		int determineMonth(std::string);
		int determineDay(std::string &);
		
		void changeToLower(std::string &);
		void removeNonDateChar(std::string &);
		bool extractNum(std::string, int &, int &);
		void removeExtraLetters(std::string, int &);
		bool retrieveDayIfNext(std::string &, size_t, std::string);
		bool getDayOfWeek(std::string, tm, int);
		bool getTdyTmr(std::string,tm, bool &);
		bool dateInLetter(std::string &);
		
		bool takeDay(std::string&, size_t &);
		bool takeMonth(std::string&, size_t &, size_t &);
		void takeYear(std::string &, std::string, std::string, size_t);
		bool isValidDate(bool &);
		
		bool checkForDate(std::string &, bool &, std::string, size_t, bool);

		int &getDay();
		int &getMonth();
		int &getYear();
};

#endif