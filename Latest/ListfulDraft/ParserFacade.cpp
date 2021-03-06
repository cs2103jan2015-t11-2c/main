//@author A0116177E
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
	_parse.removeFrontChar(_userInput);
	_parse.removeBackChar(_userInput);
	_parse.removeFrontChar(_information);
	_parse.removeBackChar(_information);
	_parse.init(_information);
	return;
}



int ParserFacade::carryOutCommand(DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, 
								  std::ostringstream &deadline) {
	int command = listClass.determineCommand(_userInput);
	
	std::string logInputParseF = "Listful: " + _userInput + " passed to ParserFacade";
	listClass.log.log(logInputParseF);
	assert(!_userInput.empty());

	int returnValue = 0;
	std::string originalStr = "";
	std::vector <int> editCat;
	bool pastDate = false;
	bool checkTime = false;
	bool isTemp = false;
	bool isDelete = false;
	
	switch(command) {
		case listClass.ADD:
			data.get_tempEntry() = data.get_emptyEntry();
			_parse.separateWord(data, pastDate, checkTime);
			listClass.add.checkDateTime(data, errMsg, pastDate, checkTime);
			if (listClass.add.addContent(data, errMsg, floating, scheduled, deadline, isTemp)) {
				listClass.log.log("Listful: ");
				returnValue = listClass.commandType::ADD;
			}
			else {
				returnValue = (listClass.commandType::ADD + 12);
			}
			break;

		case listClass.SEARCH:
			_parse.changeToLower(_information);
			if (_information == "") {
				if (listClass.search.isDisplayEmpty(data, errMsg, floating, scheduled, deadline)) {
					return listClass.commandType::SEARCH;
				}
				return (listClass.commandType::SEARCH + 12);
			}
			else {
				if (!listClass.search.displayContent(data, _information, errMsg, floating, scheduled, deadline)) {
					defaultSearchFunc(data, errMsg, floating, scheduled, deadline);
					if (data.getTempData().size() == 0) {
						return (listClass.commandType::SEARCH + 12);
					}
				}
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
			originalStr = _information;
			_parse.separateWord (data, pastDate, checkTime);
			_parse.getEditInfo(editCat, originalStr);
			if (listClass.edit.editContent(data, editCat, data.get_tempEntry().subject, errMsg, floating, scheduled, deadline, _userInput)) {
				returnValue = listClass.commandType::EDIT;
			}
			else {
				returnValue = (listClass.commandType::EDIT + 12);
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
			listClass.sortFile.getSortCat() = listClass.determineField(_information);
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
			
		case listClass.INVALID:
			if (_userInput == "") {
				return listClass.commandType::INVALID;
			}
			else {
				_parse.init(_userInput);
				defaultSearchFunc(data, errMsg, floating, scheduled, deadline);
				if (data.getTempData().size() == 0) {
					return (listClass.commandType::SEARCH + 12);
				}
				else {
					return listClass.commandType::SEARCH;
				}
			}

		default:
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



void ParserFacade::defaultSearchFunc(DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, 
									 std::ostringstream &scheduled, std::ostringstream &deadline) {
	bool pastDate = false;
	bool checkTime = false;
	_parse.separateWord(data, pastDate, checkTime);
	_parse.getMonth(data);
	if (_parse.getTime() && _parse.getDate()) {
		listClass.search.getTime(data, floating, scheduled, deadline, errMsg);
	}
	else if (_parse.getTime()) {
		data.clearData(errMsg, errMsg, errMsg);
		errMsg << "only time entered, date not entered";
		data.getTempData().clear();
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
	else if (data.get_tempEntry().month >= 1 && data.get_tempEntry().month <= 12) {
		listClass.search.getMonth(data, floating, scheduled, deadline, errMsg);
	}
	else {
		listClass.search.getSubjectSearch(data, floating, scheduled, deadline, errMsg);
	}
	return;
}

void ParserFacade::separateWord(DataStore &data, bool &i, bool &j) {
	_parse.separateWord(data, i, j);
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