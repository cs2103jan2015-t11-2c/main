#pragma once

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <fstream>
#include <vector>
#include <string>


static const std::string WELCOME_MESSAGE = "Welcome to LISTful";
static const std::string ACTION_MESSAGE = "Please choose an action: ";

static const std::string MESSAGE_ADD = "added to %s: \"%s\"";
static const std::string MESSAGE_DELETE = "deleted from %s: \"%s\"";
static const std::string MESSAGE_CLEAR = "all content deleted from %s";
static const std::string MESSAGE_EMPTY = "%s is empty";
static const std::string MESSAGE_SORT = "%s has been sorted alphabetically";

static const std::string ERROR_COMMAND = "invalid command";
static const std::string ERROR_DELETE = "text not found";
static const std::string ERROR_ADD = "\"%s\" is already inside. y to include; n to exclude";
static const std::string ERROR_SEARCH = "\"%s\" cannot be found in %s";

//static const int FILE_INDEX;

class UserInterface

{
	private:
		std::vector<std::string> _quotes;
		
	public:	
		~UserInterface(void);
		void printStarRow();
		void centralizeOutput(std::string text);
		void addQuote();
		std::string quoteOfTheDay();
		int userAction();
		int determineCommand(int choiceNum);
//		void checkFileCreated(std::string &fileName);
};
#endif