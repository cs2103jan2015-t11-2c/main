#include <iostream>
#include <string>
#include <iomanip>
#include "UserInterface.h"

UserInterface ui;

void homeScreen(){
	ui.printStarRow();
	ui.centralizeOutput(WELCOME_MESSAGE);
	ui.printStarRow();

	ui.addQuote();
	ui.centralizeOutput(ui.quoteOfTheDay());
	std::cout << std::endl;
	
	ui.centralizeOutput(ACTION_MESSAGE);
	std::cout << std::endl;
	ui.userAction();
}


int main(){
	homeScreen();

	return 0;
}

