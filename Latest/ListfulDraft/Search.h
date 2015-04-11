#ifndef DISPLAY_H
#define DISPLAY_H

#define MIN -1

#include "DataStore.h"

class Search {
	private:
		static const int FLOAT_SUB_SIZE;
		static const int NON_FLOAT_SUB_SIZE;

	public:
		Search() {};
	
		void updateDisplayData(DataStore &, int);

		bool displayContent(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getEntry(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getFloat(DataStore &, std::ostringstream &);
		void getScheduled(DataStore &, std::ostringstream &);
		void getDeadline(DataStore &, std::ostringstream &);
		void getComplete(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getOverDue(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getPriority(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getCat(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getDay(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getTime(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getToday(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getTmr(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	
		void getTempDisplay(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getReminder(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		bool getDisplay(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	
		std::string getDataString(DataStore &, int, bool, int = MIN);
		std::string getTempDataString(DataStore &, int, bool, int = MIN);

		void printSub(DataStore &, std::ostringstream &, int, int, bool, bool);
		void printDate(DataStore &, std::ostringstream &, int, bool);
		void printTime(DataStore &, std::ostringstream &, int, bool);
		void printCat(DataStore &, std::ostringstream &, int, bool);
		void printPriority(DataStore &, std::ostringstream &, int, bool);
	
		std::string getDate(DataStore &, int, bool);
		std::string getTime(DataStore &, int, bool);

		int countDigit(int);
		void printZero(int, std::ostringstream &, int);
		void printSpace(std::ostringstream &, int);

		void setColour(int);
};

#endif