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

bool Sort::compareWord(std::string &line1, std::string &line2, std::string &lineSize) {
	for (int index = 0; index < lineSize.size(); index++) {
		char word = ' ';
		if (line1[index] >= 'a' && line1[index] <= 'z') {
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
			else {
				return false;
			}
		}
		else if (line1[index] >= 'A' && line1[index] <= 'Z') {
			if (line2[index] >= 'A' && line2[index] <= 'Z') {
				return true;
			}
			else if (line2[index] >= 'a' && line2[index] <= 'z') {
				word = 'A' + (line2[index] - 'a');
				if (line1[index] > word) {
					return true;
				}
			}
			else {
				return false;
			}
		}
		else if ((line2[index] >= 'a' && line2[index] <= 'z') || 
				 (line2[index] >= 'A' && line2[index] <= 'Z')) {
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

/*void Sort::sortDate(DataStore &data) {
	int iter = 0;
	int start = 0;
	int cmp2 = 0;

	for (iter = 1; iter < data.getData().size(); ++iter) {
		cmp2 = data.getData()[iter].subject;
		for (start = 0; start < iter; ++start) {
			if ((!data.getData()[start].isFloat && !data.getData()[iter].isFloat) || (data.getData()[start].isFloat && data.getData()[iter].isFloat)) {
				line1 = data.getData()[start].subject;
				compareLineSize(line1, line2, lineSize);
				if (compareWord(line1, line2, lineSize)) {
					sortSwitch(iter, start, data);
					cmp2 = data.getData()[iter].subject;
				}
			}
		}
	}
	return;
}
*/
//Sort accordingly
bool Sort::sortContent(DataStore &data){
	switch (_category) {
		case SUBJECT:
			sortSub(data);
			break;
		case DATE:
			//sortDate(data);
			break;
		case TIME:
			break;
		case PRIORITY:
			break;
		case CATEGORY:
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