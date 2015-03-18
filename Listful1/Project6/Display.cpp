#include "Display.h"

//to determine the type of display method
int Display::determineCategory(std::string command) {
	if (command == "day") {
		return subDateCategory::DAY;
	}
	else if (command == "month") {
		return subDateCategory::MONTH;
	}
	else {
		return subDateCategory::INVALID;
	}
}
	
//to display the content
void Display::displayContent(std::string &fileName, DataStore &data, std::string command, int date) {
	if (data.getDataBaseSize() == 0) {
		std::cout << "File is currently empty.\n";
		return;
	}

	category = determineCategory(command);

	switch (category) {
		case DAY:
			for (int index = 0; index != data.getDataBaseSize(); index++) {
				if ((*(data.getDataIter())).day == date) {
					std::cout << data.getDataString(index) << '\n';
				}
			}
			break;

		case MONTH:
			for (int index = 0; index != data.getDataBaseSize(); index++) {
				if ((*(data.getDataIter())).month == date) {
					std::cout << data.getDataString(index) << '\n';
				}
			}
			break;
	
		default:
			for (int index = 0; index != data.getDataBaseSize(); index++) {
				std::cout << data.getDataString(index) << '\n';
			}
			//std::cout << "Display cannot be sorted according to the wanted category.\n";
			break;
	}
}