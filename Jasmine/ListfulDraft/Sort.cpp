#include "Sort.h"

//To swap the entries
void Sort::sortSwitch(int &index, int &start, DataStore &data){
	for(int i = 0; i < data.getData().size(); i++){
		if (i < start) {
			data.getTempData().push_back(data.getData()[i]); 
		}
		else if(i == start) {
			data.getTempData().push_back(data.getData()[index]); 
			data.getTempData().push_back(data.getData()[i]); 
		}
		else if(i != index) {
			data.getTempData().push_back(data.getData()[i]); 
		}
	}
	data.getData() = data.getTempData();
	data.getTempData().clear();
}

//Sort alphabetically
void Sort::sortSub(DataStore &data) {
	std::string line1 = "";
	std::string lineSize = "";
	std::string line2 = "";

	for (int iter = 1; iter < data.getData().size(); ++iter) {
		line2 = data.getData()[iter].subject;
		for (int start = 0; start < iter; ++start) {
			if ((data.getData()[start].isFloat == data.getData()[iter].isFloat) && (data.getData()[iter].isTimedTask == data.getData()[start].isTimedTask)) {
				if (data.getData()[start].isComplete == data.getData()[iter].isComplete) {
					line1 = data.getData()[start].subject;
					compareLineSize(line1, line2, lineSize);
					if (compareWord(line1, line2, lineSize)) {
						sortSwitch(iter, start, data);
						line2 = data.getData()[iter].subject;
					}
				}
			}
		}
	}
	return;
}

void Sort::compareLineSize(std::string &line1, std::string &line2, std::string &lineSize) {
	if (line1.size() <= line2.size()) {
		lineSize = line1;
	}
	else {
		lineSize = line2;
	}
}

bool Sort::convertAndCmp(std::string line1, std::string line2, int index, char &word) {
	if (line2[index] >= 'a' && line2[index] <= 'z') {
		if (line1[index] > line2[index]) {
			return true;
		}
	}
	else if (line2[index] >= 'A' && line2[index] <= 'Z') {
		word = 'a' + (line2[index] - 'A');
		if (line1[index] > word) {
			return true;
		}
	}
	return false;
}

bool Sort::compareWord(std::string &line1, std::string &line2, std::string &lineSize) {
	for (int index = 0; index < lineSize.size(); index++) {
		char word = ' ';
		if (line1[index] >= 'a' && line1[index] <= 'z') {
			return convertAndCmp(line1, line2, index, word);
		}
		else if (line1[index] >= 'A' && line1[index] <= 'Z') {
			return convertAndCmp(line2, line1, index, word);
		}
		else if ((line2[index] >= 'a' && line2[index] <= 'z') || (line2[index] >= 'A' && line2[index] <= 'Z')) {
			return true;
		}
		else if (line1[index] > line2[index]) {
			return true;
		}
		
		if ((index == lineSize.size() - 1) && (lineSize == line2)) {
			if ((word != ' ') && (line1[index] < word)) {
				return false;
			}
			else if ((word == ' ') && (line1[index] < line2[index])) {
				return false;
			}
			else {
				return true;
			}
		}
	}

	return false;
}

void Sort::sortDate(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if ((data.getData()[start].isFloat == data.getData()[iter].isFloat) && (data.getData()[iter].isTimedTask == data.getData()[start].isTimedTask)) {
				if (data.getData()[start].isComplete == data.getData()[iter].isComplete) {
					if (data.getData()[start].year == data.getData()[iter].year && data.getData()[start].month == data.getData()[iter].month && data.getData()[start].day > data.getData()[iter].day) {
						sortSwitch(iter, start, data);
					}
					else if (data.getData()[start].year == data.getData()[iter].year && data.getData()[start].month > data.getData()[iter].month) {
						sortSwitch(iter, start, data);
					}
					else if (data.getData()[start].year > data.getData()[iter].year) {
						sortSwitch(iter, start, data);
					}
				}
			}
		}
	}
	return;
}

void Sort::sortComplete(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if ((data.getData()[start].isFloat == data.getData()[iter].isFloat) && (data.getData()[iter].isTimedTask == data.getData()[start].isTimedTask)) {
				if (data.getData()[start].isComplete && !data.getData()[iter].isComplete) {
					sortSwitch(iter, start, data);
				}
			}
		}
	}
	return;
}

void Sort::sortTime(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if ((data.getData()[start].isFloat == data.getData()[iter].isFloat) && (data.getData()[iter].isTimedTask == data.getData()[start].isTimedTask)) {
				if (data.getData()[start].isComplete == data.getData()[iter].isComplete) {
					if (data.getData()[start].startTime > data.getData()[iter].startTime) {
						sortSwitch(iter, start, data);
					}
					else if (data.getData()[start].startTime == data.getData()[iter].startTime && data.getData()[start].endTime < data.getData()[iter].endTime) {
						sortSwitch(iter, start, data);
					}
				}
			}
		}
	}
	return;
}

int Sort::determineC(std::string word) {
	if (word == "WORK    ") {
		return catType::WORK;
	}
	else if (word == "PERSONAL") {
		return catType::PERSONAL;
	}
	else if (word == "ERRAND  ") {
		return catType::ERRAND;
	}
	else if (word == "GENERAL ") {
		return catType::GENERAL;
	}
	else {
		return catType::CINVALID;
	}
}

void Sort::sortCat(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if ((data.getData()[start].isFloat == data.getData()[iter].isFloat) && (data.getData()[iter].isTimedTask == data.getData()[start].isTimedTask)) {
				if (data.getData()[start].isComplete == data.getData()[iter].isComplete) {
					if (determineC(data.getData()[start].category) > determineC(data.getData()[iter].category)) {	
						sortSwitch(iter, start, data);
					}
				}
			}
		}
	}
	return;
}

int Sort::determineP(std::string word) {
	if (word == "LOW  ") {
		return priorityType::LOW;
	}
	else if (word == "MED  ") {
		return priorityType::MEDIUM;
	}
	else if (word == "HIGH ") {
		return priorityType::HIGH;
	}
	else {
		return priorityType::PINVALID;
	}
}

void Sort::sortPriority(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if ((data.getData()[start].isFloat == data.getData()[iter].isFloat) && (data.getData()[iter].isTimedTask == data.getData()[start].isTimedTask)) {
				if (data.getData()[start].isComplete == data.getData()[iter].isComplete) {
					if (determineP(data.getData()[start].priority) > determineP(data.getData()[iter].priority)) {	
						sortSwitch(iter, start, data);
					}
				}
			}
		}
	}
	return;
}

bool Sort::sortContent(DataStore &data){
	switch (_category) {
		case 0:
			sortSub(data);
			break;
		case 1:
			sortDate(data);
			break;
		case 2:
			sortTime(data);
			break;
		case 3:
			sortPriority(data);
			break;
		case 4:
			sortCat(data);
			break;
		default:
			return false;
	}
	return true;
}

int &Sort::getSortCat() {
	return _category;
}