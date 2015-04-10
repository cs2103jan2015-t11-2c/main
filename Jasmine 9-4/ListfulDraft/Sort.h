#ifndef SORT_H
#define SORT_H

#include "DataStore.h"

class Sort {
private:
	enum priorityType {
		LOW, MEDIUM, HIGH, PINVALID
	};

	enum catType {
		WORK, PERSONAL, ERRAND, GENERAL, CINVALID
	};

	int _category;

public:
	Sort() {};

	void sortSwitch(int &, int &, DataStore &);
	
	void sortSub(DataStore &);
	void compareLineSize(std::string &, std::string &, std::string &);
	bool compareWord(std::string &, std::string &, std::string &);
	bool convertAndCmp(std::string, std::string, int, char &);
	
	void sortComplete(DataStore &);
	void sortDate(DataStore &);
	void sortTime(DataStore &);
	void sortCat(DataStore &);
	int determineC(std::string);
	void sortPriority(DataStore &);
	int determineP(std::string);
	bool sortContent(DataStore &);
	
	bool cmpSame(DataStore & ,int, int);

	int &getSortCat();
};

#endif