#include "Edit.h"
#include "Add.h"

bool Edit::editContent(DataStore &data, int index, std::ostringstream &errMsg){
	if (data.getData().size() == 0) {
		return false;
	}
	Add add;
	
	switch (_category) {
		case 0:
			std::cout << "sub!!!!" << std::endl;
			data.getData()[index].subject= data.get_tempEntry().subject;
			break;
		case 1:
			std::cout << "date!!!!" << std::endl;
			_editEntry = data.getData()[index];
			if (data.get_tempEntry().day == 0) {
				_editEntry.isFloat = true;
			}
			_editEntry.day = data.get_tempEntry().day;
			_editEntry.month = data.get_tempEntry().month;
			_editEntry.year = data.get_tempEntry().year;

			data.getData().erase(data.getData().begin() + index - 1);
			data.get_tempEntry() = _editEntry;
			add.addContent(data, errMsg);
			break;
		
		case 2:
			std::cout << "time!!!!" << std::endl;
			_editEntry = data.getData()[index];
			if (data.get_tempEntry().startTime == data.get_tempEntry().endTime) {
				_editEntry.isTimedTask = false;
			}
			else {
				_editEntry.isTimedTask = true;
			}

			_editEntry.startTime = data.get_tempEntry().startTime;
			_editEntry.endTime = data.get_tempEntry().endTime;

			data.getData().erase(data.getData().begin() + index - 1);
			data.get_tempEntry() = _editEntry;
			add.addContent(data, errMsg);
			break;
		    
		case 3:
			std::cout << "priority!!!!" << std::endl;
			data.getData()[index].priority = data.get_tempEntry().priority;
			break;
			
		case 4:
			std::cout << "cat!!!!" << std::endl;
			data.getData()[index].category = data.get_tempEntry().category;
			break;

		default:
			return false;
	}
	return true;
}

int &Edit::getCat() {
	return _category;
}