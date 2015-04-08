#ifndef USERMESSAGE_H
#define USERMESSAGE_H

#include "Entry.h"

class UserMessage {
private:
	static const std::string MESSAGE_STAR;
	static const std::string MESSAGE_WELCOME;
	static const std::string MESSAGE_LOGIN;
	static const std::string MESSAGE_LOGIN2;
	static const std::string MESSAGE_LINE;
	static const std::string MESSAGE_DISPLAY_FLOATING;
	static const std::string MESSAGE_DISPLAY_SCHEDULE;
	static const std::string MESSAGE_DISPLAY_DEADLINE;
	static const std::string MESSAGE_COMMAND_LIST;

	static const std::string CURRENT_TIME;

	static const std::string MESSAGE_FILE_OPENED;
	static const std::string MESSAGE_FILE_CREATED;
	static const std::string MESSAGE_REMINDER;
	static const std::string MESSAGE_FREE;
	static const std::string MESSAGE_TO_DELETE;

	static const std::string MESSAGE_ADD;
	static const std::string MESSAGE_DISPLAY;
	static const std::string MESSAGE_CLEAR;
	static const std::string MESSAGE_EDIT;
	static const std::string MESSAGE_SORT;
	static const std::string MESSAGE_SEARCH;
	static const std::string MESSAGE_UNDO;
	static const std::string MESSAGE_REDO;
	static const std::string MESSAGE_DELETE;
	static const std::string ERROR_COMMAND;
	static const std::string MESSAGE_DO_NOTHING;
	static const std::string MESSAGE_CLOSE_FILE;
	static const std::string ERROR_ADD;
	static const std::string ERROR_DISPLAY;
	static const std::string ERROR_CLEAR;
	static const std::string ERROR_SEARCH;
	static const std::string ERROR_EDIT;
	static const std::string ERROR_SORT;
	static const std::string ERROR_UNDO;
	static const std::string ERROR_REDO;
	static const std::string ERROR_DELETE;
	static const std::string ERROR_DELETE_2;
	
	static const std::string ERROR_ADD_DATE;
	static const std::string ERROR_ADD_TIME;
	static const std::string ERROR_ADD_CLASH_SUBJECT;
	static const std::string ERROR_ADD_CLASH_TIME;

	std::vector <std::string> _commandMsg;

	std::vector <std::string> _fileMsg;
	
	std::vector <std::string> _displayMsg;

	std::vector <std::string> _progMsg;

	std::vector <std::string> _progErrorMsg;

	std::vector <std::string> _quotes;

public:
	UserMessage();

	std::string getTime();
	std::vector <std::string> &getQuote();
	std::vector <std::string> &getCommandMsg();
	std::vector <std::string> &getFileMsg();
	std::vector <std::string> &getProgMsg();
	std::vector <std::string> &getDisplayMsg();
};

#endif