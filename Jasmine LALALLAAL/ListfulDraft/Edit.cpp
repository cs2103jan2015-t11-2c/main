#include "Edit.h"

bool Edit::editContent(DataStore &data, int index, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline){
	if (data.getData().size() == 0 || index > data.getData().size()) {
		errMsg << "index entered is invalid";
		return false;
	}
	
	data.clearData(floating, scheduled, deadline);
	data.getTempData().clear();
	bool real = true;
	bool isTemp = false;
	Add add;
	Display show;

	switch (_category) {
		case 0:
			errMsg << " \"" << data.getData()[index].subject << "\" to \"" << data.get_tempEntry().subject << "\"";
			data.getData()[index].subject= data.get_tempEntry().subject;
			show.getChange(data, floating, scheduled, deadline);
			data.get_tempEntry().subject = errMsg.str();
			break;

		case 1:
			data.getTempData().push_back(data.get_tempEntry());
			errMsg << " \"" << show.getDate(data, index, isTemp) << "\" to \"" << show.getDate(data, 0, real) << "\"";
			editDate(data, index);
			add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
			data.get_tempEntry().subject = errMsg.str();
			break;
		
		case 2:
			data.getTempData().push_back(data.get_tempEntry());
			errMsg << " \"" << show.getTime(data, index, isTemp) << "\" to \"" << show.getTime(data, 0, real) << "\"";
			editTime(data, index);
			add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
			data.get_tempEntry().subject = errMsg.str();
			break;
		    
		case 3:
			errMsg << " \"" << data.getData()[index].priority << "\" to \"" << data.get_tempEntry().priority << "\"";
			data.getData()[index].priority = data.get_tempEntry().priority;
			show.getChange(data, floating, scheduled, deadline);
			data.get_tempEntry().subject = errMsg.str();
			break;
			
		case 4:
			errMsg << " \"" << data.getData()[index].category << "\" to \"" << data.get_tempEntry().category << "\"";
			data.getData()[index].category = data.get_tempEntry().category;
			show.getChange(data, floating, scheduled, deadline);
			data.get_tempEntry().subject = errMsg.str();
			break;

		default:
			errMsg << "category entered is invalid";
			return false;
	}
	return true;
}

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

int &Edit::getCat() {
	return _category;
}