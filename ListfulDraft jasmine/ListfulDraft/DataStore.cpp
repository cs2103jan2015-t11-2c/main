#include "DataStore.h"

std::string DataStore::getDataString(int &index) {
	std::ostringstream dataString;
	std::ostringstream time;
	std::ostringstream date;
	std::ostringstream cat;
	std::ostringstream priority;


	int sTime = countDigit(_dataBase[index].startTime);
	int eTime = countDigit(_dataBase[index].endTime);
	int nDay = countDigit(_dataBase[index].day);
	int nMonth = countDigit(_dataBase[index].month);
	int nYear = countDigit(_dataBase[index].year);

	dataString << _dataBase[index].subject << "\n" << "Date: " << std::setw(10); 
	printZero(nDay, dataString, 2);
	dataString << _dataBase[index].day << '/';	
	printZero(nMonth, dataString, 2);
	dataString << _dataBase[index].month << '/' << _dataBase[index].year << "Time: " << std::setw(10);
	printZero(sTime, dataString, 4);
	dataString << _dataBase[index].startTime << '-';
	printZero(eTime, dataString, 4);
	dataString << _dataBase[index].endTime;

	dataString << "Category: " << std::setw(6) << _dataBase[index].category;
	dataString << "Priority: " << _dataBase[index].priority << '\n';
	return dataString.str();
}

int DataStore::countDigit(int &num) {
	int count = 0;
	int tNum = num;

	if (num == 0) {
		return 1;
	}

	while (tNum > 0) {
		count++;
		tNum = tNum/10;
	}
	return count;
}

void DataStore::printZero(int &num, std::ostringstream &dataString, int count) {
	while (num < count) {
		dataString << '0';
		num++;
	}
	return;
}

/*void DataStore::entryType(std::string &subject, int &star_tTime, int &endTime, int &day, int &month, int &year, std::string &impt, std::string &category) {
	_tempEntry.index = index;
	_tempEntry.subject = subject;
	_tempEntry.star_tTime = star_tTime;
	_tempEntry.endTime = endTime;
	_tempEntry.day = day;
	_tempEntry.month = month;
	_tempEntry.year = year;
	_tempEntry.impt = impt;
	_tempEntry.category = category;
}*/

void DataStore::updateFile(std::string fileName) {
	std::ofstream writeFile;

	savePrevFile();
	writeFile.open(fileName);
	for (int index = 0; index != _dataBase.size(); index++) {
		writeFile << (index + 1) << ". " << getDataString(index) << "\n";
	}
	writeFile.close();
	return;
}

void DataStore::savePrevFile() {
	_pastData.push(_dataBase);

	if (_pastData.size() > 10) {
		_pastData.pop();
	}
	return;
}

void DataStore::undoData() {
	redoData();
	_dataBase = _pastData.back();
	return;
}

void DataStore::redoData() {
	_futureData.push(_dataBase);

	if (_futureData.size() > 10) {
		_futureData.pop();
	}
	return;
}

std::vector <Entry> &DataStore::getData() {
	return _dataBase;
}

Entry &DataStore::getEntry(int index) {
	return _dataBase[index];
}
	
Entry &DataStore::get_tempEntry() {
	return _tempEntry;
}