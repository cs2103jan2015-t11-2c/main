#include "Edit.h"

bool Edit::editContent(DataStore &data, int index, std::ostringstream &errMsg){
	if (data.getData().size() == 0 || index > data.getData().size()) {
		return false;
	}
	bool isTemp = false;
	Add add;
	
	switch (_category) {
		case 0:
			data.getData()[index].subject= data.get_tempEntry().subject;
			break;

		case 1:
			editDate(data, add, index, errMsg, isTemp);
			break;
		
		case 2:
			editTime(data, add, index, errMsg, isTemp);
			break;
		    
		case 3:
			data.getData()[index].priority = data.get_tempEntry().priority;
			break;
			
		case 4:
			data.getData()[index].category = data.get_tempEntry().category;
			break;

		default:
			return false;
	}
	return true;
}

void Edit::editTime(DataStore &data, Add &add, int index, std::ostringstream &errMsg, bool isTemp) {
	_editEntry = data.getData()[index];
	if (data.get_tempEntry().startTime == data.get_tempEntry().endTime) {
		_editEntry.isTimedTask = false;
	}
	else {
		_editEntry.isTimedTask = true;
	}

	_editEntry.startTime = data.get_tempEntry().startTime;
	_editEntry.endTime = data.get_tempEntry().endTime;
	data.getData().erase(data.getData().begin() + index);
	data.get_tempEntry() = _editEntry;
	add.addContent(data, errMsg, isTemp);
	return;
}

void Edit::editDate(DataStore &data, Add &add, int index, std::ostringstream &errMsg, bool isTemp) {
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
	add.addContent(data, errMsg, isTemp);
	return;
}

int &Edit::getCat() {
	return _category;
}