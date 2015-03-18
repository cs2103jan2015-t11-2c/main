#ifndef DATASTORE_H
#define DATASTORE_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>

class DataStore {

private:
	struct Entries {
		int index;
		std::string subject;
		int day;
		int month;
		int year;
		int startTime;
		int endTime;
		std::string impt; //importance
		std::string category;
	};

	std::vector <Entries> dataBase;

//	std::ifstream readFile;

	std::vector <Entries>::iterator dataIter;

	Entries tempEntry;

public:
	
	DataStore() {};

	std::string getDataString(int);
	void updateFile(std::string &);
	void entryType(int &, std::string &, int &, int &, int &, int &, int &, std::string &, std::string &);
	int countDigit(int &);

	std::vector <Entries>::iterator getDataIter() {
		return dataIter = dataBase.begin();
	}

	Entries getEntry() {
		return tempEntry;
	}

	std::vector <Entries> getDataBase() {
		return dataBase;
	}

	int getDataBaseSize() {
		return dataBase.size();
	}

	void clearDataBase() {
		dataBase.clear();
	}

	void updateDataBase();
	void deleteDataBase(std::vector <Entries>::iterator);
	void inputCommand();
	int checkCommand();
	void executeCommand();
	
};

#endif