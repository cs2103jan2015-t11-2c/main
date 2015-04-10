#include "DataStore.h"
#include "Display.h"

//To update the text file in the computer
void DataStore::updateFile(DataStore &data) {
	bool updateFile = true;
	Display display;

	std::ofstream writeFile(_fileName);
	for (int index = 0; index != _dataBase.size(); index++) {
		writeFile << (index + 1) << ". " << display.getDataString(data, index, updateFile) << " | Priority: " << _dataBase[index].priority << "\n\n";
	}

	//To create an empty file
	if (_dataBase.size() == 0) {
		writeFile << "";
	}
	writeFile.close();
	return;
}

//Saves a previous version for undo and redo functionalities
void DataStore::savePrevFile() {
	_pastData.push_back(_dataBase);
	_futureData.clear();
	_futureActionLog.clear();

	_pastTempData.push_back(_tempDataBase);
	_futureTempData.clear();
	return;
}

bool DataStore::undoData(DataStore &data, std::ostringstream &errMsg) {
	if (_pastData.size() <= 1) {
		return false;
	}

	errMsg << "\n\n" << _pastActionLog.back();
	_futureActionLog.push_back(_pastActionLog.back());
	_pastActionLog.pop_back();
	
	_futureData.push_back(_dataBase);
	_pastData.pop_back();
	_dataBase = _pastData.back();

	_futureTempData.push_back(_pastTempData.back());
	_tempDataBase = _pastTempData.back();
	_pastTempData.pop_back();
	updateFile(data);
	return true;
}

bool DataStore::redoData(DataStore &data, std::ostringstream &errMsg) {
	if (_futureData.empty()) {
		return false;
	}
	
	errMsg << "\n\n" << _futureActionLog.back();
	_pastActionLog.push_back(_futureActionLog.back());
	_futureActionLog.pop_back();

	_dataBase = _futureData.back();
	_futureData.pop_back();
	_pastData.push_back(_dataBase);

	_pastTempData.push_back(_futureTempData.back());
	_tempDataBase = _futureTempData.back();
	_futureTempData.pop_back();
	updateFile(data);
	return true;
}

void DataStore::savePrevAction(std::string msg) {
	_pastActionLog.push_back(msg);
	
	if (_pastActionLog.size() > 12) {
		_pastActionLog.erase(_pastActionLog.begin());
	}
	return;
}

void DataStore::clearData(std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	floating.str("");
	floating.clear();
	scheduled.str("");
	scheduled.clear();
	deadline.str("");
	deadline.clear();
	return;
}

void DataStore::init(std::string fileName) {
	_fileName = fileName;
}

std::vector <Entry> &DataStore::getData() {
	return _dataBase;
}

std::vector <int> &DataStore::getTempIndexList() {
	return _tempIndexList;
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