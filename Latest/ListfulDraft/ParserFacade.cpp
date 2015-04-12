#include "ParserFacade.h"

ParserFacade::ParserFacade() {
	_isRun = true;
}

//Separates the user input to be the command string and information string and initialises private vector in parser
void ParserFacade::init(std::string command) {
	size_t start = 0;
	size_t end;
	
	_parse.getNextWord(command, start, end);
	if (end == std::string::npos) {
		_userInput = command;
		_parse.removeBackChar(_userInput);
		_information = "";
		return;
	}
	_userInput = command.substr(start, end - 1);
	_information = command.substr(end);
	_parse.removeBackChar(_userInput);
	_parse.removeFrontChar(_information);
	_parse.removeBackChar(_information);
	_parse.init(_information);
	return;
}



int ParserFacade::carryOutCommand(Classes &listClass, DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int command = listClass.determineCommand(_userInput);
	
	int returnValue = 0;
	int index = 0;
	std::string str = "";
	bool pastDate = false;
	bool checkTime = false;
	bool isTemp = false;
	bool isDelete = false;
	
	switch(command) {
		case listClass.ADD:
			data.get_tempEntry() = data.get_emptyEntry();
			_parse.separateWord(listClass, data, pastDate, checkTime);
			listClass.add.checkDateTime(data, errMsg, pastDate, checkTime);
			if (listClass.add.addContent(data, errMsg, floating, scheduled, deadline, isTemp)) {
				returnValue = listClass.commandType::ADD;
			}
			else {
				returnValue = (listClass.commandType::ADD + 12);
			}
			break;

		case listClass.SEARCH:
			_parse.changeToLower(_information);
			if (_information == "") {
				if (listClass.search.getDisplay(data, errMsg, floating, scheduled, deadline)) {
					return listClass.commandType::SEARCH;
				}
				return (listClass.commandType::SEARCH + 12);
			}
			else {
				if (!listClass.search.displayContent(data, _information, errMsg, floating, scheduled, deadline)) {
					_parse.separateWord(listClass, data, pastDate, checkTime);
					if (_parse.getTime() && _parse.getDate()) {
						listClass.search.getTime(data, floating, scheduled, deadline, errMsg);
					}
					else if (_parse.getTime()) {
						listClass.search.getFloat(data, floating, errMsg);
					}
					else if (_parse.getDate()) {
						listClass.search.getDay(data, floating, scheduled, deadline, errMsg);
					}
					else if (_parse.getCat()) {
						listClass.search.getCat(data, floating, scheduled, deadline, errMsg);
					}
					else if (_parse.getPriority()) {
						listClass.search.getPriority(data, floating, scheduled, deadline, errMsg);
					}
					else if (_parse.getComplete()) {
						listClass.search.getComplete(data, floating, scheduled, deadline, errMsg);
					}
					else {
						return (listClass.commandType::SEARCH + 12);
					}
				}
				std::cout << "efh" << std::endl;
				return listClass.commandType::SEARCH;
			}

		case listClass.CLEAR:
			if (listClass.clearFile.clearFile(data)) {
				returnValue = listClass.commandType::CLEAR;
			}
			else {
				returnValue = (listClass.commandType::CLEAR + 12);
			}
			break;

		case listClass.EDIT:
			str = _information;
			_parse.separateWord(listClass, data, pastDate, checkTime);
			if (!_parse.getEditInfo(data, listClass, index, listClass.edit.getCat(), str, errMsg)) {
				returnValue = (listClass.commandType::EDIT + 12);
			}
			else {
				if (listClass.edit.editContent(data, index - 1, errMsg, floating, scheduled, deadline)) {
					returnValue = listClass.commandType::EDIT;
				}
				else if (errMsg == "" && listClass.edit.checkComplete(data, _information, errMsg, floating, scheduled, deadline, _userInput)) {
					returnValue = (listClass.commandType::EDIT + 3);
				}
				else {
				std::cout << "st" << std::endl;
					returnValue = (listClass.commandType::EDIT + 12);
				}
			}
			break;

		case listClass.REMOVE:
			if (listClass.remove.deleteContent(data, _information, errMsg, floating, scheduled, deadline, isDelete)) {
				returnValue = listClass.commandType::REMOVE;
			}
			else if (!isDelete) {
				returnValue = (listClass.commandType::REMOVE + 13);
			}
			else {
				returnValue = (listClass.commandType::REMOVE + 12);
			}
			break;

		case listClass.REDO:
			if (data.redoData(data, errMsg)) {
				listClass.search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
				return listClass.commandType::REDO;
			}
			return (listClass.commandType::REDO + 12);

		case listClass.UNDO:
			if (data.undoData(data, errMsg)) {
				listClass.search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
				return listClass.commandType::UNDO;
			}
			return (listClass.commandType::UNDO + 12);

		case listClass.SORT:
			_parse.changeToLower(_information);
			listClass.sortFile.getSortCat() = listClass.determineSubCat(_information);
			if (listClass.sortFile.sortContent(data)) {
				returnValue = listClass.commandType::SORT;
			}
			else {
				returnValue = (listClass.commandType::SORT + 12);
			}
			break;

		case listClass.EXIT:
			_isRun = false;
			return (listClass.commandType::EXIT + 1); 

		default:
			if (_userInput == "") {
				return listClass.commandType::DO_NOTHING;
			}
			return listClass.commandType::INVALID;
	}
	data.updateFile(data);
	data.savePrevFile();
	return returnValue;
}



bool ParserFacade::isRunProgram() {
	return _isRun;
}

bool ParserFacade::isHelp(std::string input) {
	if (input == "?") {
		return true;
	}
	return false;
}



void ParserFacade::separateWord(Classes &listClass, DataStore &data, bool &i, bool &j) {
	_parse.separateWord(listClass, data, i, j);
	return;
}
	
void ParserFacade::removeFrontChar(std::string &str) {
	_parse.removeFrontChar(str);
	return;
}
	
void ParserFacade::removeBackChar(std::string &str) {
	_parse.removeBackChar(str);
	return;
}

void ParserFacade::readFile(std::string info) {
	_parse.init(info);
	return;
}