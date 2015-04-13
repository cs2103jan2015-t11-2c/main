//@author A0116237L
#include "Sort.h"

//to sort content
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

//To swap the entries
void Sort::shiftPos(int &index, int &start, DataStore &data){
	data.getTempData().clear();
	data.getTempIndexList().clear();

	for(int i = 0; i < data.getData().size(); i++){
		if (i < start) {
			data.getTempData().push_back(data.getData()[i]); 
			data.getTempData()[i].referenceNo = i + 1;
		}
		else if(i == start) {
			data.getTempData().push_back(data.getData()[index]);
			data.getTempData()[i].referenceNo = i + 1;
			data.getTempData().push_back(data.getData()[i]); 
			data.getTempData()[i + 1].referenceNo = i + 2;
		}
		else if(i != index) {
			data.getTempData().push_back(data.getData()[i]);
			data.getTempData()[i].referenceNo = i + 2;
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
			if (cmpSame(data, start, iter)) {
				line1 = data.getData()[start].subject;
				compareLineSize(line1, line2, lineSize);
				if (isLargerChar(line1, line2, lineSize)) {
					shiftPos(iter, start, data);
					line2 = data.getData()[iter].subject;
				}
			}
		}
	}
	return;
}

//to compare line size
void Sort::compareLineSize(std::string &line1, std::string &line2, std::string &lineSize) {
	if (line1.size() <= line2.size()) {
		lineSize = line1;
	}
	else {
		lineSize = line2;
	}
}

//to check if its uper case
bool Sort::isUpperCase(std::string line1, std::string line2, int index, char &word) {
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
 
//to see if its a larger character
bool Sort::isLargerChar(std::string &line1, std::string &line2, std::string &lineSize) {
	for (int index = 0; index < lineSize.size(); index++) {
		char word = ' ';
		if (line1[index] >= 'a' && line1[index] <= 'z') {
			return isUpperCase(line1, line2, index, word);
		}
		else if (line1[index] >= 'A' && line1[index] <= 'Z') {
			return isUpperCase(line2, line1, index, word);
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

//to sort by date
void Sort::sortDate(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if (cmpSame(data, start, iter)) {
				if (data.getData()[start].year == data.getData()[iter].year && 
					data.getData()[start].month == data.getData()[iter].month && 
					data.getData()[start].day > data.getData()[iter].day) {
					shiftPos(iter, start, data);
				}
				else if (data.getData()[start].year == data.getData()[iter].year && 
					data.getData()[start].month > data.getData()[iter].month) {
					shiftPos(iter, start, data);
				}
				else if (data.getData()[start].year > data.getData()[iter].year) {
					shiftPos(iter, start, data);
				}
			}
		}
	}
	return;
}

//to sort by completed status
void Sort::sortComplete(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if ((data.getData()[start].isFloat == data.getData()[iter].isFloat) && 
				(data.getData()[iter].isTimedTask == data.getData()[start].isTimedTask)) {
				if (data.getData()[start].isComplete && !data.getData()[iter].isComplete) {
					shiftPos(iter, start, data);
				}
			}
		}
	}
	return;
}

//to sort by time
void Sort::sortTime(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if (cmpSame(data, start, iter)) {
				if (data.getData()[start].startTime > data.getData()[iter].startTime) {
					shiftPos(iter, start, data);
				}
				else if (data.getData()[start].startTime == data.getData()[iter].startTime && 
					data.getData()[start].endTime < data.getData()[iter].endTime) {
					shiftPos(iter, start, data);
				}
			}
		}
	}
	return;
}


//to determine category to be sorted
int Sort::determineCategory(std::string word) {
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
//to sort by category
void Sort::sortCat(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if (cmpSame(data, start, iter)) {
				if (determineCategory(data.getData()[start].category) > determineCategory(data.getData()[iter].category)) {	
					shiftPos(iter, start, data);
				}
			}
		}
	}
	return;
}


//to determine priority entered
int Sort::determinePriority(std::string word) {
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

//to sort by priority
void Sort::sortPriority(DataStore &data) {
	for (int iter = 1; iter < data.getData().size(); ++iter) {
		for (int start = 0; start < iter; ++start) {
			if (cmpSame(data, start, iter)) {
				if (determinePriority(data.getData()[start].priority) > determinePriority(data.getData()[iter].priority)) {	
					shiftPos(iter, start, data);
				}
			}
		}
	}
	return;
}


//to compare the tasks
bool Sort::cmpSame(DataStore &data, int start, int iter) {
	if (data.getData()[start].isFloat == data.getData()[iter].isFloat) {
		if (data.getData()[iter].isTimedTask == data.getData()[start].isTimedTask) {
			if (data.getData()[start].isComplete == data.getData()[iter].isComplete) {
				return true;
			}
		}
	}
	return false;
}

//getter function for category
int &Sort::getSortCat() {
	return _category;
}