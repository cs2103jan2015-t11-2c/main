#include "Edit.h"
//to update entry to done status
bool Edit::checkAll(DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::string input) {
	int size = 0;
	std::vector <Entry> holdTempTask;

	while (size < data.getTempData().size()) {
		if (input == "uncheck" || input == "uncomplete") {
			data.getData()[data.getTempIndexList()[size]].isComplete = false;
			data.get_tempEntry().subject = "uncompleted all of the below";
		}
		else {
			data.getData()[data.getTempIndexList()[size]].isComplete = true;
			data.get_tempEntry().subject = "completed all of the below";
		}
		size++;
	}
	data.clearData(errMsg, floating, scheduled);
	data.clearData(floating, scheduled, deadline);
	search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
	return true;
}
//to check if task is done
bool Edit::checkComplete(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::string input) {
	size_t found = info.find_first_of(" ");
	int index = 0;
	std::vector <int> checkList;
	std::vector <Entry> holdTempTask;

	//To complete all tasks shown
	if (info == "all") {
		return checkAll(data, errMsg, floating, scheduled, deadline, input);
	}

	std::cout << "size: " << data.getTempIndexList().size()<<std::endl;
	while (!info.empty()) {
		if (found == std::string::npos) {
			found = info.size();
		}
		index = atoi(info.substr(0, found).c_str());
		if (index > data.getTempData().size()) {
			errMsg << "index out of range";
			return false;
		}
		else if (!checkList.empty()) {
			if (isRepeat(data, checkList, index - 1)) {
				errMsg << data.get_tempEntry().subject;
				return false;
			}
		}
		if (input == "uncheck" || input == "uncomplete") {
			data.getData()[data.getTempIndexList()[index - 1]].isComplete = false;
		}
		else {
			data.getData()[data.getTempIndexList()[index - 1]].isComplete = true;
		}
		checkList.push_back(data.getData()[data.getTempIndexList()[index - 1]].referenceNo);
		if (found == info.size()) {
			info = "";
		}
		else {
			info = info.substr(found + 1);
			found = info.find_first_of(" ");
		}
	}
	updateTemp(data, checkList);
	holdTempTask = data.getTempData();
	sort.sortComplete(data);
	data.getTempData() = holdTempTask;
	std::cout << data.getTempData().size() << std::endl;
	data.clearData(floating, scheduled, deadline);
	search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
	data.get_tempEntry().subject = "completed";
	return true;
}


//to edit content
bool Edit::editContent(DataStore &data, std::vector <int> editCat, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::string input, int index) {
	if (data.getData().size() == 0) {
		errMsg << "file is empty";
		return false;
	}
	
	bool real = true;
	bool isTemp = false;
	
	if (input == "check" || input == "done" || input == "complete" || input == "completed" || input == "uncheck" || input == "uncomplete") {
		return checkComplete(data, info, errMsg, floating, scheduled, deadline, input);
	}

	if (index < 0 && !getEditIndex(info, index) && data.getTempData().size() != 1) {
		errMsg << "no index entered";
		return false;
	}
	
	if (index < 0 && data.getTempData().size() == 1) {
		index = 1;
	}
	
	if (errMsg != "") {
		errMsg << "\n";
	}
	
	data.get_tempEntry().subject = info;
	data.getTempData().clear();
	data.getTempData().push_back(data.get_tempEntry());
	
	switch (editCat[0]) {
		case 0:
			if (data.get_tempEntry().subject == "") {
				break;
			}
			errMsg << " \"" << data.getData()[data.getTempIndexList()[index]].subject << "\" to \"";
			errMsg << data.get_tempEntry().subject << "\"";
			data.getData()[data.getTempIndexList()[index]].subject = data.get_tempEntry().subject;
			_editEntry = data.get_tempEntry();
			break;

		case 1:
			errMsg << " \"" << search.getDate(data, data.getTempIndexList()[index], isTemp) << "\" to \"";
			errMsg << search.getDate(data, 0, real) << "\"";
			editDate(data, data.getTempIndexList()[index]);
			_editEntry = data.getTempData().front();
			add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
			index = 0;
			break;

		case 2:
			errMsg << " \"" << search.getTime(data, data.getTempIndexList()[index], isTemp) << "\" to \"";
			errMsg << search.getTime(data, 0, real) << "\"";
			editTime(data, data.getTempIndexList()[index]);
			_editEntry = data.getTempData().front();
			add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
			index = 0;
			break;
		    
		case 3:
			errMsg << " \"" << data.getData()[data.getTempIndexList()[index]].priority << "\" to \"";
			errMsg << data.get_tempEntry().priority << "\"";
			data.getData()[data.getTempIndexList()[index]].priority = data.get_tempEntry().priority;
			_editEntry = data.get_tempEntry();
			break;
			
		case 4:
			errMsg << " \"" << data.getData()[data.getTempIndexList()[index]].category << "\" to \"";
			errMsg << data.get_tempEntry().category << "\"";
			data.getData()[data.getTempIndexList()[index]].category = data.get_tempEntry().category;
			_editEntry = data.get_tempEntry();
			break;

		default:
			return false;
	}

	data.get_tempEntry() = data.getData()[data.getTempIndexList()[index]];
	data.clearData(floating, scheduled, deadline);
	search.getEntry(data, floating, scheduled, deadline, errMsg);
	data.get_tempEntry().subject = "";

	if (editCat.size() > 1) {
		index = 0;
		data.get_tempEntry() = _editEntry;
		_editEntry = data.getTempData().front();
		editCat.erase(editCat.begin());
		editContent(data, editCat, info, errMsg, floating, scheduled, deadline, input, index);
	}
	return true;
}
//to get the index of edited content
bool Edit::getEditIndex(std::string &info, int &index) {
	
	size_t found = info.find_first_of("0123456789");
	std::string checkNum = info;
	index = 0;
	while (found != std::string::npos && found < checkNum.size() && checkNum[found] >= '0' && checkNum[found] <= '9') {
		index = (index * 10) + (checkNum[found] - '0');
		checkNum = checkNum.substr(found + 1);
	}
	
	if (index != 0) {
		found = info.find_first_of("0123456789");
		info = info.substr(0, found) + checkNum;
		while (info.size() != 0 && info[0] == ' ') {
			info = info.substr(1);
		}
		while (info.size() != 0 && info.back() == ' ') {
			info = info.substr(0, info.size() - 1);
		}
		index--;
		return true;
	}
	else {
		return false;
	}
}
//to edit time
void Edit::editTime(DataStore &data, int index) {
	_editEntry = data.getData()[index];
	
	if (data.get_tempEntry().startTime != data.get_tempEntry().endTime && !_editEntry.isFloat) {
		_editEntry.isTimedTask = true;
	}
	else {
		_editEntry.isTimedTask = false;
	}
			
	_editEntry.startTime = data.get_tempEntry().startTime;
	_editEntry.endTime = data.get_tempEntry().endTime;
	data.getData().erase(data.getData().begin() + index);
	data.get_tempEntry() = _editEntry;
	return;
}
//to edit date
void Edit::editDate(DataStore &data, int index) {
	_editEntry = data.getData()[index];
	if (data.get_tempEntry().day == 0) {
		_editEntry.isFloat = true;
	}
	else {
		_editEntry.isFloat = false;
	}
	_editEntry.day = data.get_tempEntry().day;
	_editEntry.month = data.get_tempEntry().month;
	_editEntry.year = data.get_tempEntry().year;
	data.getData().erase(data.getData().begin() + index);
	data.get_tempEntry() = _editEntry;
	return;
}
//to update temporary storage 
void Edit::updateTemp(DataStore &data, std::vector <int> list) {
	data.getTempData().clear();
	data.getTempIndexList().clear();
		
	for (int i = 0; !list.empty(); i++) {
		if (i < data.getData().size() && data.getData()[i].referenceNo == list.back()) {
			data.getTempIndexList().push_back(i);
			data.getTempData().push_back(data.getData()[i]);
			list.pop_back();
		}
		
		if (i == data.getData().size()) {
			i = -1;
		}
	}
	return;
}
//to check if the index is repeated
bool Edit::isRepeat(DataStore &data, std::vector <int> list, int index) {
	for (int j = 0; j < list.size(); j++) {
		if (list[j] == data.getData()[index].referenceNo) {
			data.get_tempEntry().subject = "repeated index to check complete found";
			return true;
		}
	}
	return false;
}