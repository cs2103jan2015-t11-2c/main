#include "UserMessage.h"

const std::string UserMessage::MESSAGE_STAR = "********************************************************************************";
const std::string UserMessage::MESSAGE_WELCOME = "                           *** Welcome to Listful ***\n";
const std::string UserMessage::MESSAGE_ACTION = "Please choose an action:";
const std::string UserMessage::MESSAGE_COMMAND_LIST = "  1)Add   2)Display   3)Delete   4)Clear   5)Edit   6)Sort   7)Search   8)Exit  ";

const std::string UserMessage::CLEAR_SCREEN = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

const std::string UserMessage::MESSAGE_FILE_CREATED = "new file, %s, created and ready for use";
const std::string UserMessage::MESSAGE_FILE_OPENED = "%s is open and ready for use";

const std::string UserMessage::MESSAGE_ADD = "added to %s: \"%s\" %s";
const std::string UserMessage::MESSAGE_DISPLAY = "";
const std::string UserMessage::MESSAGE_DELETE = "deleted from %s: \"%s\"";
const std::string UserMessage::MESSAGE_CLEAR = "all content deleted from %s";
const std::string UserMessage::MESSAGE_EDIT = "%s has been changed accordingly";
const std::string UserMessage::MESSAGE_SORT = "%s has been sorted";
const std::string UserMessage::MESSAGE_SEARCH = "results for searching in %s: \"%s\"";
const std::string UserMessage::MESSAGE_UNDO = "undid previous change";
const std::string UserMessage::MESSAGE_REDO = "redid previous undo";
const std::string UserMessage::ERROR_COMMAND = "invalid command";
const std::string UserMessage::ERROR_ADD = "%s";
const std::string UserMessage::ERROR_DISPLAY = "%s is already empty";
const std::string UserMessage::ERROR_DELETE = "entry to delete not found";
const std::string UserMessage::ERROR_CLEAR = "%s is already empty";
const std::string UserMessage::ERROR_EDIT = "entry to edit not found";
const std::string UserMessage::ERROR_SORT = "%s does not contain the category specified: \"%s\"";
const std::string UserMessage::ERROR_SEARCH = "keyword cannot be found in %s";
const std::string UserMessage::ERROR_UNDO = "no previous changes to undo";
const std::string UserMessage::ERROR_REDO = "no previous undo to redo";

UserMessage::UserMessage() {
	_commandMsg.push_back(MESSAGE_ADD);
	_commandMsg.push_back(MESSAGE_DISPLAY);
	_commandMsg.push_back(MESSAGE_DELETE);
	_commandMsg.push_back(MESSAGE_CLEAR);
	_commandMsg.push_back(MESSAGE_EDIT);
	_commandMsg.push_back(MESSAGE_SORT);
	_commandMsg.push_back(MESSAGE_SEARCH);
	_commandMsg.push_back(MESSAGE_UNDO);
	_commandMsg.push_back(MESSAGE_REDO);
	_commandMsg.push_back(ERROR_COMMAND);
	_commandMsg.push_back(ERROR_ADD);
	_commandMsg.push_back(ERROR_DISPLAY);
	_commandMsg.push_back(ERROR_DELETE);
	_commandMsg.push_back(ERROR_CLEAR);
	_commandMsg.push_back(ERROR_EDIT);
	_commandMsg.push_back(ERROR_SORT);
	_commandMsg.push_back(ERROR_SEARCH);
	_commandMsg.push_back(ERROR_UNDO);
	_commandMsg.push_back(ERROR_REDO);

	_progMsg.push_back(MESSAGE_STAR);
	_progMsg.push_back(MESSAGE_WELCOME);
	_progMsg.push_back(MESSAGE_STAR);
	_progMsg.push_back(MESSAGE_ACTION);
	_progMsg.push_back(MESSAGE_COMMAND_LIST);

	_fileMsg.push_back(MESSAGE_FILE_OPENED);
	_fileMsg.push_back(MESSAGE_FILE_CREATED);

	_quotes.push_back("Mistakes are proof that you are trying.");
	_quotes.push_back("Be kind, for everyone you meet is fighting a harder battle.");
	_quotes.push_back("Never stop doing your best just because someone doesn't give you credit.");
	_quotes.push_back("It's not who you are that holds you back, it's who you think you're not.");
}

std::vector <std::string> &UserMessage::getQuote() {
	return _quotes;
}

std::vector <std::string> &UserMessage::getCommandMsg() {
	return _commandMsg;
}

std::vector <std::string> &UserMessage::getFileMsg() {
	return _fileMsg;
}

std::vector <std::string> &UserMessage::getProgMsg() {
	return _progMsg;
}

std::string &UserMessage::getClearScreen() {
	std::string msg = CLEAR_SCREEN;
	return msg;
}