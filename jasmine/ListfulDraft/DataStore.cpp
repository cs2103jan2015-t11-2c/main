#include "DataStore.h"

void DataStore::init(std::string fileName) {
	_fileName = fileName;
	savePrevFile();
}

//To output one whole entry by itself
std::string DataStore::getDataString(int index) {
	std::ostringstream dataString;
	std::ostringstream time;
	std::ostringstream date;
	std::ostringstream cat;
	std::ostringstream priority;

	//Gets the number of digits for each entry variable
	int sTime = countDigit(_dataBase[index].startTime);
	int eTime = countDigit(_dataBase[index].endTime);
	int nDay = countDigit(_dataBase[index].day);
	int nMonth = countDigit(_dataBase[index].month);
	int nYear = countDigit(_dataBase[index].year);

	//Form one whole string from the whole entry with standard sized columns
	dataString << _dataBase[index].subject << std::endl << "Date: " ;
	if (_dataBase[index].day == 0) {
		dataString << "-";
		printSpace(dataString, 11);
	}
	else {
		printZero(nDay, dataString, 2);
		dataString << _dataBase[index].day << '/';	
		printZero(nMonth, dataString, 2);
		dataString << _dataBase[index].month << '/' << _dataBase[index].year;
		printSpace(dataString, 2);
	}
	dataString << "Time: ";
	if (_dataBase[index].startTime == 0 && _dataBase[index].endTime == 0) {
		dataString << "-";
		printSpace(dataString, 11);
	}
	else {
		printZero(sTime, dataString, 4);
		dataString << _dataBase[index].startTime << '-';
		printZero(eTime, dataString, 4);
		dataString << _dataBase[index].endTime;
		printSpace(dataString, 3);
	}
	dataString << "Category: " << _dataBase[index].category;
	dataString << "Priority: " << _dataBase[index].priority << std::endl;
	return dataString.str();
}

std::string DataStore::getTempDataString(int index) {
	std::ostringstream dataString;
	std::ostringstream time;
	std::ostringstream date;
	std::ostringstream cat;
	std::ostringstream priority;

	//Gets the number of digits for each entry variable
	int sTime = countDigit(_tempDataBase[index].startTime);
	int eTime = countDigit(_tempDataBase[index].endTime);
	int nDay = countDigit(_tempDataBase[index].day);
	int nMonth = countDigit(_tempDataBase[index].month);
	int nYear = countDigit(_tempDataBase[index].year);

	//Form one whole string from the whole entry with standard sized columns
	dataString << _tempDataBase[index].subject << std::endl << "Date: " ;
	if (_tempDataBase[index].day == 0) {
		dataString << "-";
		printSpace(dataString, 11);
	}
	else {
		printZero(nDay, dataString, 2);
		dataString << _tempDataBase[index].day << '/';	
		printZero(nMonth, dataString, 2);
		dataString << _tempDataBase[index].month << '/' << _tempDataBase[index].year;
		printSpace(dataString, 2);
	}
	dataString << "Time: ";
	if (_tempDataBase[index].startTime == 0 && _tempDataBase[index].endTime == 0) {
		dataString << "-";
		printSpace(dataString, 11);
	}
	else {
		printZero(sTime, dataString, 4);
		dataString << _tempDataBase[index].startTime << '-';
		printZero(eTime, dataString, 4);
		dataString << _tempDataBase[index].endTime;
		printSpace(dataString, 3);
	}
	dataString << "Category: " << _tempDataBase[index].category;
	dataString << "Priority: " << _tempDataBase[index].priority << std::endl;
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

//To ensure that the no of digits for time and date are 4 and 2 respectively
void DataStore::printZero(int &num, std::ostringstream &dataString, int count) {
	while (num < count) {
		dataString << '0';
		num++;
	}
	return;
}

//To equalize the columns of each output entry
void DataStore::printSpace(std::ostringstream &dataString, int count) {
	while (count > 0) {
		dataString << " ";
		count--;
	}
}

//To update the text file in the computer
void DataStore::updateFile() {
	std::ofstream writeFile;

	writeFile.open(_fileName);
	if (_dataBase.size() == 0) {
		writeFile << "";
	}
	else {
		for (int index = 0; index != _dataBase.size(); index++) {
			if (index != _dataBase.size() - 1) {
				writeFile << (index + 1) << ". " << getDataString(index) << std::endl;
			}
			else {
				writeFile << (index + 1) << ". " << getDataString(index);
			}
		}
	}
	writeFile.close();
	return;
}

//Saves a previous version for undo and redo functionalities
void DataStore::savePrevFile() {
	_pastData.push_back(_dataBase);
	_futureData.clear();

	if (_pastData.size() > 12) {
		_pastData.erase(_pastData.begin());
	}
	return;
}

bool DataStore::undoData() {
	if (_pastData.empty()) {
		return false;
	}

	_futureData.push_back(_dataBase);
	_pastData.pop_back();
	_dataBase = _pastData[_pastData.size() - 1];
	updateFile();
	return true;
}

bool DataStore::redoData() {
	if (_futureData.empty()) {
		return false;
	}
	
	_dataBase = _futureData[_futureData.size() - 1];
	_pastData.push_back(_dataBase);
	updateFile();
	_futureData.pop_back();
	return true;
}

std::vector <Entry> &DataStore::getData() {
	return _dataBase;
}

std::vector <Entry> &DataStore::getTempData() {
	return _tempDataBase;
}

Entry &DataStore::getEntry(int index) {
	return _dataBase[index];
}
	
Entry &DataStore::get_tempEntry() {
	return _tempEntry;
}

std::string DataStore::getDate(Entry task) {
	std::ostringstream dataString;

	int sTime = countDigit(task.startTime);
	int eTime = countDigit(task.endTime);
	int nDay = countDigit(task.day);
	int nMonth = countDigit(task.month);
	int nYear = countDigit(task.year);

	if (task.day == 0) {
		return dataString.str();
	}
	else {
		printZero(nDay, dataString, 2);
		dataString << task.day << '/';	
		printZero(nMonth, dataString, 2);
		dataString << task.month << '/' << task.year;
		printSpace(dataString, 2);
	}
	return dataString.str();
}
   
std::string DataStore::getTime(Entry task) {
	std::ostringstream dataString;

	int sTime = countDigit(task.startTime);
	int eTime = countDigit(task.endTime);
	int nDay = countDigit(task.day);
	int nMonth = countDigit(task.month);
	int nYear = countDigit(task.year);

	if (task.startTime == 0 && task.endTime == 0) {
		return dataString.str();
	}
	else {
		printZero(sTime, dataString, 4);
		dataString << task.startTime << '-';
		printZero(eTime, dataString, 4);
		dataString << task.endTime;
		printSpace(dataString, 3);
	}
	return dataString.str();
}