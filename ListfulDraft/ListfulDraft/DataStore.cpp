#include "DataStore.h"

std::string DataStore::getDataString(int &index) {
	std::ostringstream dataString;

	int sTime = countDigit(_dataBase[index].star_tTime);
	int eTime = countDigit(_dataBase[index].endTime);
	int nDay = countDigit(_dataBase[index].day);
	int nMonth = countDigit(_dataBase[index].month);
	int nYear = countDigit(_dataBase[index].year);

	dataString << _dataBase[index].subject << "\nDate: ";
	printDateZero(nDay, dataString);
	dataString << _dataBase[index].day << '/';	
	printDateZero(nMonth, dataString);
	dataString << _dataBase[index].month << '/' << _dataBase[index].year << "\t\_tTime: ";
	prin_tTimeZero(sTime, dataString);
	dataString << _dataBase[index].star_tTime << '-';
	prin_tTimeZero(eTime, dataString);
	dataString << _dataBase[index].endTime;

	dataString << "\t\tCategory: " << _dataBase[index].category << '\n';

	return dataString.str();

}

int DataStore::countDigit(int &num) {
	int count = 0;
	int tNum = num;

	while (tNum > 0) {
		count++;
		tNum = tNum/10;
	}
	return count;
}

void DataStore::prin_tTimeZero(int &time, std::ostringstream &dataString) {
	while (time < 4) {
		dataString << '0';
		time++;
	}
}

void DataStore::printDateZero(int &date, std::ostringstream &dataString) {
	if (date < 2) {
		dataString << '0';
	}
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

void DataStore::updateFile(std::string &fileName) {
	std::ofstream writeFile;

	savePrevFile();
	writeFile.open(fileName);
	for (int index = 0; index != _dataBase.size(); index++) {
		writeFile << index << ". " << getDataString(index) << "\n";
	}
	writeFile.close();
}

void DataStore::savePrevFile() {
	_pastData.push(_dataBase);

	if (_pastData.size() > 10) {
		_pastData.pop();
	}
}

void DataStore::undoData() {
	redoData();
	_dataBase = _pastData.back();
}

void DataStore::redoData() {
	_futureData.push(_dataBase);

	if (_futureData.size() > 10) {
		_futureData.pop();
	}
}

Entry DataStore::getEntry(int &index) {
	return _dataBase[index];
}
	
Entry DataStore::get_tempEntry() {
	return _tempEntry;
}