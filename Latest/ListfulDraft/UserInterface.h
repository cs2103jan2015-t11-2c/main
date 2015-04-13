#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FileLocation.h"
#include "UserMessage.h"

#define MAX 1000

class UserInterface {
	private:
		std::string _userInput;

		int i;
		char msgToUser[MAX];
		std::string quote;
		
		Classes listClass;
		ParserFacade parseF;
		DataStore data;
		UserMessage outputToUser;
		FileLocation file;
		Log log;
		
		std::ostringstream errMsg;
		std::ostringstream floating;
		std::ostringstream scheduled;
		std::ostringstream deadline;

	public:
		UserInterface() {};

		void runProgram();
		
		void clearData(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getStringToDisplay(std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void getOutputToUser(int, DataStore &, std::string, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, 
						     std::ostringstream &, bool, bool);
		
		void readFileName(std::string &);
		void extractFileName(std::string &, std::string &, FileLocation &);
		std::string getPath();
		
		void remindAndDueHeader(bool, bool, std::ostringstream &, std::ostringstream &, std::ostringstream &, int, std::ostringstream &, 
								std::string);
		void showReminder(DataStore, std::string &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void showOverDue(DataStore, std::string &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		
		void outputCommand();
		void defaultScreen(ParserFacade &);
		void startUpScreen(DataStore &, FileLocation &, ParserFacade &, std::string &, std::string &, std::ostringstream &, std::ostringstream &, 
						   std::ostringstream &, std::ostringstream &, bool, bool);
		void homeScreen();
		std::string quoteOfTheDay();
		std::string getCurrent(int = 0);
		void centralizePrintToUser(std::string, std::ostringstream &);
};

#endif