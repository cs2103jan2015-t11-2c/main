#include "DataStore.h"
#include "Display.h"

/*
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
	if (_dataBase[index].priority == "HIGH") {
		setColour(12);
	}
	else if (_dataBase[index].priority == "MED") {
		setColour(14);
	}
	dataString << _tempDataBase[index].subject << std::endl;
	setColour(7);

	dataString << "Date: " ;
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

	dataString << "Completed: ";
	if (_tempDataBase[index].isComplete) {
		dataString << "yes ";
	}
	else {
		dataString << "no  ";
	}
	return dataString.str();
}
*/

//To update the text file in the computer
void DataStore::updateFile(DataStore &data) {
	bool updateFile = true;
	Display display;

	std::ofstream writeFile(_fileName);
	for (int index = 0; index != _dataBase.size(); index++) {
		if (index != _dataBase.size() - 1) {
			writeFile << (index + 1) << ". " << display.getDataString(data, index, updateFile) << " | Priority: " << _dataBase[index].priority << "\n\n";
		}
		else {
			writeFile << (index + 1) << ". " << display.getDataString(data, index, updateFile) << " | Priority: " << _dataBase[index].priority;
		}
	}
	writeFile.close();
	return;
}

//Saves a previous version for undo and redo functionalities
void DataStore::savePrevFile() {
	_pastData.push_back(_dataBase);
	_futureData.clear();
	_futureActionLog.clear();

	if (_pastData.size() > 12) {
		_pastData.erase(_pastData.begin());
	}
	return;
}

bool DataStore::undoData(DataStore &data, std::ostringstream &errMsg) {
	std::cout << "oi" << std::endl;
	if (_pastData.empty()) {
		std::cout << "empty!" << std::endl;
		return false;
	}
	
	std::cout << "whut!" << std::endl;
	errMsg << _pastActionLog.back();
	_futureActionLog.push_back(_pastActionLog.back());
	_pastActionLog.pop_back();
	
	std::cout << "zzzz!" << std::endl;
	_futureData.push_back(_dataBase);
	_pastData.pop_back();
	_dataBase = _pastData.back();
	updateFile(data);
	return true;
}

bool DataStore::redoData(DataStore &data, std::ostringstream &errMsg) {
	if (_futureData.empty()) {
		return false;
	}
	
	errMsg << _futureActionLog.back();
	_pastActionLog.push_back(_futureActionLog.back());
	_futureActionLog.pop_back();

	_dataBase = _futureData.back();
	_futureData.pop_back();
	_pastData.push_back(_dataBase);
	updateFile(data);
	return true;
}

std::string &DataStore::getFileName() {
	return _fileName;
}

std::vector <Entry> &DataStore::getData() {
	return _dataBase;
}

std::vector <Entry> &DataStore::getTempData() {
	return _tempDataBase;
}

std::vector <std::string> &DataStore::getPastActionLog() {
	return _pastActionLog;
}

std::vector <std::string> &DataStore::getFutureActionLog() {
	return _futureActionLog;
}

Entry &DataStore::getEntry(int index) {
	return _dataBase[index];
}
	
Entry &DataStore::get_tempEntry() {
	return _tempEntry;
}

Entry &DataStore::get_emptyEntry() {
	return _emptyEntry;
}
/*
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
   */
/*
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
*/