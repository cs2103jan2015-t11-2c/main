#include "Classes.h"

int Classes::determineCommand(std::string _userInput) {
	if (_userInput == "add" || _userInput == "1" || _userInput == "addto") {
		return commandType::ADD;
	}
	else if (_userInput == "display" || _userInput == "2" || _userInput == "show") {
		return commandType::DISPLAY;
	}
	else if (_userInput == "delete" || _userInput == "3" || _userInput == "remove") {
		return commandType::REMOVE;
	}
	else if (_userInput == "clear" || _userInput == "4" || _userInput == "reset") {
		return commandType::CLEAR;
	}
	else if (_userInput == "edit" || _userInput == "5" || _userInput == "append") {
		return commandType::EDIT;
	}
	else if (_userInput == "sort" || _userInput == "6") {
		return commandType::SORT;
	}
	else if (_userInput == "search" || _userInput == "7") {
		return commandType::SEARCH;
	}
	else if (_userInput == "exit" || _userInput == "8") {
		return commandType::EXIT;
	}
	else if (_userInput == "undo") {
		return commandType::UNDO;
	}
	else if (_userInput == "redo") {
		return commandType::REDO;
	}
	else {
		return commandType::INVALID;
	}
}

int Classes::determineSubCat(std::string info) {
	if (info == "date") {
		return subCategory::DATE;
	}
	else if (info == "time") {
		return subCategory::TIME;
	}
	else if (info == "priority" || info == "impt" || info == "importance") {
		return subCategory::PRIORITY;
	}
	else if (info == "category" || info == "cat") {
		return subCategory::CATEGORY;
	}
	else if (info == "sub" || info == "subject" || info == "alphabetically") {
		return subCategory::SUBJECT;
	}
	else {
		return subCategory::INVALIDCAT;
	}
}

int Classes::determineP(std::string str) {
	if (str == "LOW" || str == "L") {
		return priorityType::LOW;
	}
	else if (str == "MEDIUM" || str == "MED" || str == "M") {
		return priorityType::MEDIUM;
	}
	else if (str == "HIGH" || str == "H") {
		return priorityType::HIGH;
	}
	else {
		return priorityType::PINVALID;
	}
}

int Classes::determineC(std::string word) {
	if (word == "WORK     " || word == "WORK") {
		return catType::WORK;
	}
	else if (word == "PERSONAL " || word == "PERSONAL") {
		return catType::PERSONAL;
	}
	else if (word == "ERRAND   " || word == "ERRAND") {
		return catType::ERRAND;
	}
	else if (word == "GENERAL " || word == "GENERAL") {
		return catType::GENERAL;
	}
	else {
		return catType::CINVALID;
	}
}