#include "Completion.h"

void updateCompleted(DataStore &data, int index){
	data.getTempData().clear();

	data.getData()[index].isComplete = true;
	data.getTempData().push_back(data.getData()[index]);
	data.getData().erase(data.getData().begin()+index);
	data.getData().insert(data.getData().end(), data.getTempData()[0]);

	return;
}

bool checkCompleted(DataStore &data, int index){
	bool complete = false;
	
	if (data.getData()[index].isComplete == true){
		complete = true;
	}

	return complete;
}