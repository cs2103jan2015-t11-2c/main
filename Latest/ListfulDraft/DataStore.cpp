#include "DataStore.h"
#include "Search.h"

void DataStore::init(std::string fileName) {
	_fileName = fileName;
}



//To update the text file in the computer
void DataStore::updateFile(DataStore &data) {
	bool updateFile = true;
	Search search;

	std::ofstream writeFile(_fileName);
	for (int index = 0; index != _dataBase.size(); index++) {
		writeFile << (index + 1) << ". " << search.getDataString(data, index, updateFile) << " | ";
		if (_dataBase[index].isComplete) {
			writeFile << "yes\n\n";
		}
		else {
			writeFile << "no\n\n";
		}
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
	_undoData.push_back(_dataBase);
	_redoData.clear();
	_redoActionLog.clear();

	_undoTempData.push_back(_tempDataBase);
	_redoTempData.clear();
	return;
}


//to undo data
bool DataStore::undoData(DataStore &data, std::ostringstream &errMsg) {
	if (_undoData.size() <= 1) {
		return false;
	}

	errMsg << "\n\n" << _undoActionLog.back();
	_redoActionLog.push_back(_undoActionLog.back());
	_undoActionLog.pop_back();
	
	_redoData.push_back(_dataBase);
	_undoData.pop_back();
	_dataBase = _undoData.back();

	_redoTempData.push_back(_undoTempData.back());
	_tempDataBase = _undoTempData.back();
	_undoTempData.pop_back();
	updateFile(data);
	return true;
}
//to redo data
bool DataStore::redoData(DataStore &data, std::ostringstream &errMsg) {
	if (_redoData.empty()) {
		return false;
	}
	
	errMsg << "\n\n" << _redoActionLog.back();
	_undoActionLog.push_back(_redoActionLog.back());
	_redoActionLog.pop_back();

	_dataBase = _redoData.back();
	_redoData.pop_back();
	_undoData.push_back(_dataBase);

	_undoTempData.push_back(_redoTempData.back());
	_tempDataBase = _redoTempData.back();
	_redoTempData.pop_back();
	updateFile(data);
	return true;
}
//to save the previous command entered
void DataStore::savePrevAction(std::string msg) {
	_undoActionLog.push_back(msg);
	
	if (_undoActionLog.size() > 12) {
		_undoActionLog.erase(_undoActionLog.begin());
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



std::vector <Entry> &DataStore::getData() {
	return _dataBase;
}

std::vector <int> &DataStore::getTempIndexList() {
	return _tempIndexList;
}

std::vector <Entry> &DataStore::getTempData() {
	return _tempDataBase;
}

std::vector <std::string> &DataStore::getUndoActionLog() {
	return _undoActionLog;
}

std::vector <std::string> &DataStore::getRedoActionLog() {
	return _redoActionLog;
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