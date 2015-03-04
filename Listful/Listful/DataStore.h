#ifndef DATASTORE_H
#define DATASTORE_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;

class DataStore {

private:
	struct Entries {
		int index;
		string subject;
		int time;
		int date;
		string impt; //importance
		string category;
	};

	vector <Entries> dataBase;
	string command; //stores command from user

	//This enumerator contains all possible commands
	enum commandType {
		ADD, DELETE, DISPLAY, CLEAR, EXIT, SEARCH, INVALID
	};

	//This variable will contain the identified command
	int usercommand;

public:
	DataStore();
	void inputCommand();
	int checkCommand();
	void executeCommand();

	vector <Entries>  DataStore::getDataBase() {
	return dataBase;
}

};

#endif