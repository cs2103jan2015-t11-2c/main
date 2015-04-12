#include "UserMessage.h"

const std::string UserMessage::MESSAGE_COMMAND_LIST = "     1)Add    2)Search    3)Delete    4)Clear    5)Edit    6)Sort    8)Exit     ";
const std::string UserMessage::MESSAGE_LINE = " ------------------------------------------------------------------------------ ";
const std::string UserMessage::MESSAGE_STAR = "********************************************************************************";
const std::string UserMessage::MESSAGE_WELCOME = "                           *** Listful %s ***                           ";
const std::string UserMessage::MESSAGE_LOGIN = " ~ For help, enter [?] to search the above list of commands available             NOTE: you can [undo] and [redo] actions as well                               ";
const std::string UserMessage::MESSAGE_LOGIN2 = " Please enter a file name (and location to save your file if you wish)           -> ";
const std::string UserMessage::MESSAGE_DISPLAY_FLOATING = "  TO DO(s)                                       | Time      | Category |        ================================================|===========|==========|====== ";
const std::string UserMessage::MESSAGE_DISPLAY_SCHEDULE = "  SCHEDULED TASK(s)                 | Date       | Time      | Category |        ===================================|============|===========|==========|====== ";
const std::string UserMessage::MESSAGE_DISPLAY_DEADLINE = "  DEADLINE TASK(s)                  | Date       | Time      | Category |        ===================================|============|===========|==========|====== ";

const std::string UserMessage::CURRENT_TIME = "                                                                      [ %s ] ";

const std::string UserMessage::MESSAGE_FILE_CREATED = " loading... new %s created and ready for use";
const std::string UserMessage::MESSAGE_FILE_OPENED = " loading... %s is open and ready for use";
const std::string UserMessage::MESSAGE_REMINDER = "                    REMINDER(s) for today and the next 2 days                   %s%s%s%s";
const std::string UserMessage::MESSAGE_OVERDUE = "                                    OVERDUE                                     %s%s%s%s";
const std::string UserMessage::MESSAGE_NO_OVERDUE = " you have no overdue tasks ^^";
const std::string UserMessage::MESSAGE_FREE = " you have no upcoming tasks due today and next 2 days :)";

const std::string UserMessage::MESSAGE_ADD = " added to %s: [%s]%s%s";
const std::string UserMessage::MESSAGE_SEARCH = "%s%s%s%s";
const std::string UserMessage::MESSAGE_CLEAR = " all content deleted from %s";
const std::string UserMessage::MESSAGE_EDIT = " changed %s: task [%s] from %s%s";
const std::string UserMessage::MESSAGE_SORT = " %s has been sorted";
const std::string UserMessage::MESSAGE_DELETE = " task(s) deleted from %s:%s%s%s";
const std::string UserMessage::MESSAGE_COMPLETE = " updating %s.. %s%s%s";
const std::string UserMessage::MESSAGE_UNDO = " undid previous change for %s:%s%s%s";
const std::string UserMessage::MESSAGE_REDO = " redid undo for %s:%s%s%s";
const std::string UserMessage::ERROR_COMMAND = " invalid command entered";
const std::string UserMessage::MESSAGE_CLOSE_FILE = " %s saved at%sListful bids you farewell...";
const std::string UserMessage::MESSAGE_DO_NOTHING = "";
const std::string UserMessage::ERROR_ADD = " invalid input entered (no subject found)";
const std::string UserMessage::ERROR_SEARCH = " %s is unable to search (%s)";
const std::string UserMessage::ERROR_CLEAR = " %s is already empty with no tasks to clear";
const std::string UserMessage::ERROR_EDIT = " %s cannot be edited (%s)";
const std::string UserMessage::ERROR_SORT = " %s does not contain the category specified: %s";
const std::string UserMessage::ERROR_DELETE = " entry to delete not found in %s (%s)";
const std::string UserMessage::ERROR_DELETE_2 = " multiple entries found, please select one (or more) to delete by its index";
const std::string UserMessage::ERROR_UNDO = " no previous changes to undo";
const std::string UserMessage::ERROR_REDO = " no previous undo to redo";

const std::string UserMessage::ERROR_ADD_DATE = " date entered has already past (undo/edit adviced)";
const std::string UserMessage::ERROR_ADD_TIME = " end time entered earlier then start time (undo/edit adviced)";

UserMessage::UserMessage() {
	_commandMsg.push_back(MESSAGE_ADD);
	_commandMsg.push_back(MESSAGE_SEARCH);
	_commandMsg.push_back(MESSAGE_CLEAR);
	_commandMsg.push_back(MESSAGE_EDIT);
	_commandMsg.push_back(MESSAGE_SORT);
	_commandMsg.push_back(MESSAGE_DELETE);
	_commandMsg.push_back(MESSAGE_COMPLETE);
	_commandMsg.push_back(MESSAGE_UNDO);
	_commandMsg.push_back(MESSAGE_REDO);
	_commandMsg.push_back(ERROR_COMMAND);
	_commandMsg.push_back(MESSAGE_CLOSE_FILE);
	_commandMsg.push_back(MESSAGE_DO_NOTHING);
	_commandMsg.push_back(ERROR_ADD);
	_commandMsg.push_back(ERROR_SEARCH);
	_commandMsg.push_back(ERROR_CLEAR);
	_commandMsg.push_back(ERROR_EDIT);
	_commandMsg.push_back(ERROR_SORT);
	_commandMsg.push_back(ERROR_DELETE);
	_commandMsg.push_back(ERROR_DELETE_2);
	_commandMsg.push_back(ERROR_UNDO);
	_commandMsg.push_back(ERROR_REDO);
											
	_progMsg.push_back(MESSAGE_COMMAND_LIST);	
	_progMsg.push_back(MESSAGE_LINE);				
	_progMsg.push_back(MESSAGE_STAR);
	_progMsg.push_back(MESSAGE_WELCOME);
	_progMsg.push_back(MESSAGE_STAR);							
	_progMsg.push_back(MESSAGE_LOGIN);				
	_progMsg.push_back(MESSAGE_LOGIN2);
	
	_displayMsg.push_back(MESSAGE_DISPLAY_FLOATING);
	_displayMsg.push_back(MESSAGE_DISPLAY_SCHEDULE);
	_displayMsg.push_back(MESSAGE_DISPLAY_DEADLINE);

	_fileMsg.push_back(MESSAGE_FILE_OPENED);
	_fileMsg.push_back(MESSAGE_FILE_CREATED);
	_fileMsg.push_back(MESSAGE_REMINDER);
	_fileMsg.push_back(MESSAGE_FREE);
	_fileMsg.push_back(MESSAGE_OVERDUE);
	_fileMsg.push_back(MESSAGE_NO_OVERDUE);

	_quotes.push_back("Mistakes are proof that you are trying.");
	_quotes.push_back("Be kind, for everyone you meet is fighting a harder battle.");
	_quotes.push_back("Never stop doing your best just because someone doesn't give you credit.");
	_quotes.push_back("It's not who you are that holds you back, it's who you think you're not.");
	_quotes.push_back("It does not matter how slowly you go as long as you do not stop.");
	_quotes.push_back("You have to learn the rules of the game. And then you have to play better than anyone else.");
	_quotes.push_back("With the new day comes new strength and new thoughts.");
	_quotes.push_back("The secret of getting ahead is getting started.");
	_quotes.push_back("Expect problems and eat them for breakfast.");
	_quotes.push_back("Don't watch the clock; do what it does. Keep going.");
	_quotes.push_back("Setting goals is the first step in turning the invisible into the visible.");
	_quotes.push_back("Do not wait to strike till the iron is hot; but make it hot by striking.");
	_quotes.push_back("Motivation will almost always beat mere talent.");
	_quotes.push_back("What you do today can improve all your tomorrows.");
	_quotes.push_back("The gift is the journey.");
	_quotes.push_back("Everything that can happen will happen.");
	_quotes.push_back("Step by step and the thing is done.");
	_quotes.push_back("The will to succeed is important, but what's more important is the will to prepare.");
}

std::string UserMessage::getTime() {
	std::string timer = CURRENT_TIME;
	return timer;
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

std::vector <std::string> &UserMessage::getDisplayMsg() {
	return _displayMsg;
}
