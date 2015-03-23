#ifndef DATASTORE_H
#define DATASTORE_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <assert.h>

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
	std::vector <Entries> tempDataBase;
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

	std::vector <Entries> getTempDataBase() {
		return tempDataBase;
	}

	int getDataBaseSize() {
		return dataBase.size();
	}

	void clearDataBase() {
		dataBase.clear();
	}

	std::string getSubject(int index){
		return dataBase[index].subject;
	}

	int getDay(int index){
		return dataBase[index].day;
	}
	int getMonth(int index){
		return dataBase[index].month;
	}
	int getYear(int index){
		return dataBase[index].year;
	}
	int getStartTime(int index){
		return dataBase[index].startTime;
	}
	std::string printTempDataBase();
	void clearTempDataBase();
	void switchDataBase();
	void updateTempDataBase( Entries );
	void updateDataBase();
	void deleteDataBase(std::vector <Entries>::iterator);
	void inputCommand();
	int checkCommand();
	void executeCommand();

	void editSubject(std::string, int);
	void editTime(int , int, int);
	void editDate(int , int, int, int);
};

#endif