#include "Completion.h"

void updateCompleted(DataStore &data, int index){
	
	data.getData()[index].isComplete = true;

	return;
}

bool checkCompleted(DataStore &data, int index){
	bool complete = false;
	
	if (data.getData()[index].isComplete == true){
		complete = true;
	}

	return complete;
}