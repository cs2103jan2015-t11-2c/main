#include "ParserFacade.h"

ParserFacade::ParserFacade() {
	_isEnd = false;
}

bool ParserFacade::isRunProgram() {
	return _isEnd;
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

bool ParserFacade::isHelp(std::string input) {
	if (input == "?") {
		return true;
	}
	return false;
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
				returnValue = (listClass.commandType::ADD + 13);
			}
			break;

		case listClass.DISPLAY:
			_parse.changeToLower(_information);
			if (_information == "") {
				if (listClass.display.getDisplay(data, errMsg, floating, scheduled, deadline)) {
					return listClass.commandType::DISPLAY;
				}
				return (listClass.commandType::DISPLAY + 13);
			}
			else {
				if (!listClass.display.displayContent(data, _information, errMsg, floating, scheduled, deadline)) {
					_parse.separateWord(listClass, data, pastDate, checkTime);
					if (_parse.getTime() && _parse.getDate()) {
						listClass.display.getTime(data, floating, scheduled, deadline);
					}
					else if (_parse.getTime()) {
						listClass.display.getFloat(data, floating);
					}
					
					else if (_parse.getDate()) {
						listClass.display.getDay(data, floating, scheduled, deadline);
					}
					else if (_parse.getCat()) {
						listClass.display.getCat(data, floating, scheduled, deadline);
					}
					else if (_parse.getPriority()) {
						listClass.display.getPriority(data, floating, scheduled, deadline);
					}
					else if (_parse.getComplete()) {
						listClass.display.getComplete(data, floating, scheduled, deadline);
					}
					else {
						return (listClass.commandType::DISPLAY + 13);
					}
					return listClass.commandType::DISPLAY;
				}
				return listClass.commandType::DISPLAY;
			}

		case listClass.CLEAR:
			if (listClass.clearFile.clearFile(data)) {
				returnValue = listClass.commandType::CLEAR;
			}
			else {
				returnValue = (listClass.commandType::CLEAR + 13);
			}
			break;

		case listClass.EDIT: 
			str = _information;
			_parse.separateWord(listClass, data, pastDate, checkTime);
			if (!_parse.getEditDelete(data, listClass, index, listClass.edit.getCat(), str, errMsg)) {
				if (listClass.edit.checkComplete(data, _information, errMsg, floating, scheduled, deadline, _userInput)) {
					returnValue = (listClass.commandType::EDIT + 4);
				}
				else {
					returnValue = (listClass.commandType::EDIT + 13);
				}
			}
			else {
				if (listClass.edit.editContent(data, index - 1, errMsg, floating, scheduled, deadline)) {
					returnValue = listClass.commandType::EDIT;
				}
				else {
					returnValue = (listClass.commandType::EDIT + 13);
				}
			}
			break;

		case listClass.REMOVE:
			if (listClass.remove.deleteContent(data, _information, errMsg, floating, scheduled, deadline, isDelete)) {
				returnValue = listClass.commandType::REMOVE;
			}
			else if (!isDelete) {
				returnValue = (listClass.commandType::REMOVE + 16);
			}
			else {
				returnValue = (listClass.commandType::REMOVE + 13);
			}
			break;

		case listClass.REDO:
			if (data.redoData(data, errMsg)) {
				listClass.display.getTempDisplay(data, floating, scheduled, deadline);
				return listClass.commandType::REDO;
			}
			return (listClass.commandType::REDO + 12);

		case listClass.UNDO:
			if (data.undoData(data, errMsg)) {
				listClass.display.getTempDisplay(data, floating, scheduled, deadline);
				return listClass.commandType::UNDO;
			}
			return (listClass.commandType::UNDO + 12);

		case listClass.SEARCH: {
			size_t found = _information.find_first_of(" ");
			if (found == std::string::npos) {
				found = _information.size();
			}
			std::string command, keyword;
			command = _information.substr(0, found);
			keyword = _information.substr(found + 1);
			_parse.removeBackChar(keyword);
			_parse.removeFrontChar(keyword);
			listClass.searchFile.getCat() =  listClass.determineSubCat(command);
			if (listClass.searchFile.searchFile(data, keyword, errMsg, floating, scheduled, deadline)) {
				returnValue = listClass.commandType::SEARCH;
			}
			returnValue = (listClass.commandType::SEARCH + 13);
			}
			break;

		case listClass.SORT:
			_parse.changeToLower(_information);
			listClass.sortFile.getSortCat() = listClass.determineSubCat(_information);
			if (listClass.sortFile.sortContent(data)) {
				returnValue = listClass.commandType::SORT;
			}
			else {
				returnValue = (listClass.commandType::SORT + 13);
			}
			break;

		case listClass.EXIT:
			_isEnd = true;
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