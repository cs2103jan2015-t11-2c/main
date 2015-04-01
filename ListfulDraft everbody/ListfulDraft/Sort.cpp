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
};

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

//Sort alphabetically
void Sort::sortSub(DataStore &data) {
	int iter = 0;
	int start = 0;
	std::string line1 = "";
	std::string lineSize = "";
	std::string line2 = "";

	for (iter = 1; iter < data.getData().size(); ++iter) {
		line2 = data.getData()[iter].subject;
		for (start = 0; start < iter; ++start) {
			if ((!data.getData()[start].isFloat && !data.getData()[iter].isFloat) || (data.getData()[start].isFloat && data.getData()[iter].isFloat)) {
				line1 = data.getData()[start].subject;
				compareLineSize(line1, line2, lineSize);
				if (compareWord(line1, line2, lineSize)) {
					sortSwitch(iter, start, data);
					line2 = data.getData()[iter].subject;
				}
			}
		}
	}
	return;
}

void Sort::sortDate(DataStore &data) {
	int iter = 0;
	int start = 0;
	int year2 = 0;
	int month2 = 0;
	int day2 = 0;

	for (iter = 1; iter < data.getData().size(); ++iter) {
		year2 = data.getData()[iter].year;
		month2 = data.getData()[iter].month;
		day2 = data.getData()[iter].day;
		for (start = 0; start < iter; ++start) {
			if (!data.getData()[start].isFloat && !data.getData()[iter].isFloat) {
				if (data.getData()[start].year == year2 && data.getData()[start].month == month2 && data.getData()[start].day > day2) {
					sortSwitch(iter, start, data);
					year2 = data.getData()[iter].year;
					month2 = data.getData()[iter].month;
					day2 = data.getData()[iter].day;
				}
				else if (data.getData()[start].year == year2 && data.getData()[start].month > month2) {
					sortSwitch(iter, start, data);
					year2 = data.getData()[iter].year;
					month2 = data.getData()[iter].month;
					day2 = data.getData()[iter].day;
				}
				else if (data.getData()[start].year > year2) {
					sortSwitch(iter, start, data);
					year2 = data.getData()[iter].year;
					month2 = data.getData()[iter].month;
					day2 = data.getData()[iter].day;
				}
			}
		}
	}
	return;
}

void Sort::sortTime(DataStore &data) {
	int iter = 0;
	int start = 0;
	int sTime2 = 0;
	int eTime2 = 0;

	for (iter = 1; iter < data.getData().size(); ++iter) {
		sTime2 = data.getData()[iter].startTime;
		eTime2 = data.getData()[iter].endTime;
		for (start = 0; start < iter; ++start) {
			if ((!data.getData()[start].isFloat && !data.getData()[iter].isFloat) || (data.getData()[start].isFloat && data.getData()[iter].isFloat)) {
				if (data.getData()[start].startTime > sTime2) {
					sortSwitch(iter, start, data);
					sTime2 = data.getData()[iter].startTime;
					eTime2 = data.getData()[iter].endTime;
				}
				else if (data.getData()[start].startTime == sTime2 && data.getData()[start].endTime < eTime2) {
					sortSwitch(iter, start, data);
					sTime2 = data.getData()[iter].startTime;
					eTime2 = data.getData()[iter].endTime;
				}
			}
		}
	}
	return;
}

int Sort::determineC(std::string word) {
	if (word == "WORK     ") {
		return catType::WORK;
	}
	else if (word == "PERSONAL ") {
		return catType::PERSONAL;
	}
	else if (word == "ERRAND   ") {
		return catType::ERRAND;
	}
	else if (word == "INBOX    ") {
		return catType::INBOX;
	}
	else {
		return catType::CINVALID;
	}
}

void Sort::sortCat(DataStore &data) {
	int iter = 0;
	int start = 0;
	int p1 = 0;
	int p2 = 0;

	for (iter = 1; iter < data.getData().size(); ++iter) {
		p2 = determineC(data.getData()[iter].category);
		for (start = 0; start < iter; ++start) {
			p1 = determineP(data.getData()[start].category);
			if ((!data.getData()[start].isFloat && !data.getData()[iter].isFloat) || (data.getData()[start].isFloat && data.getData()[iter].isFloat)) {
				if (p1 > p2) {	
					sortSwitch(iter, start, data);
					p2 = determineC(data.getData()[iter].priority);
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
	int iter = 0;
	int start = 0;
	int p1 = 0;
	int p2 = 0;

	for (iter = 1; iter < data.getData().size(); ++iter) {
		p2 = determineP(data.getData()[iter].priority);
		for (start = 0; start < iter; ++start) {
			p1 = determineP(data.getData()[start].priority);
			if ((!data.getData()[start].isFloat && !data.getData()[iter].isFloat) || (data.getData()[start].isFloat && data.getData()[iter].isFloat)) {
				if (p1 > p2) {	
					sortSwitch(iter, start, data);
					p2 = determineP(data.getData()[iter].priority);
				}
			}
		}
	}
	return;
}

//Sort accordingly
bool Sort::sortContent(DataStore &data){
	switch (_category) {
		case SUBJECT:
			sortSub(data);
			break;
		case DATE:
			sortDate(data);
			break;
		case TIME:
			sortTime(data);
			break;
		case PRIORITY:
			sortPriority(data);
			break;
		case CATEGORY:
			sortCat(data);
			break;
		default:
			return false;
	}

	data.updateFile();
	data.savePrevFile();
	return true;
}

int &Sort::getSortCat() {
	return _category;
}