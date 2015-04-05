#include "Message.h"

/*const std::string Message::MESSAGE_WELCOME = "*** Welcome to Listful ***";
const std::string Message::MESSAGE_ACTION = "Please choose an action: ";

const std::string Message::MESSAGE_ADD = "added to %s: \"%s\"";
const std::string Message::MESSAGE_DELETE = "deleted from %s: \"%s\"";
const std::string Message::MESSAGE_CLEAR = "all content deleted from %s";
const std::string Message::MESSAGE_EMPTY = "%s is empty";
const std::string Message::MESSAGE_SORT = "%s has been sorted alphabetically";
const std::string Message::MESSAGE_EDIT = "%s has been edited";
const std::string Message::MESSAGE_SEARCH = "results of '%s':\n";
const std::string Message::MESSAGE_UNDO = "undid previous change";
const std::string Message::MESSAGE_REDO = "redid previous undo";

const std::string Message::ERROR_COMMAND = "invalid command";
const std::string Message::ERROR_DELETE = "text not found";
const std::string Message::ERROR_ADD = "\"%s\" is already inside. y to include; n to exclude";
const std::string Message::ERROR_SEARCH = "\"%s\" cannot be found in %s";
const std::string Message::ERROR_EDIT;
const std::string Message::ERROR_SORT;
const std::string Message::ERROR_UNDO;
const std::string Message::ERROR_REDO;*/

Message::Message(void)
{
}


Message::~Message(void)
{
}

void Message::addMessage(){
	_messages.push_back("*** Welcome to Listful ***");
	_messages.push_back("Please choose an action: ");

	_messages.push_back("added to %s: \"%s\"");					//add message
	_messages.push_back("deleted from %s: \"%s\"");				//delete message
	_messages.push_back("all content deleted from %s");			//clear message
	_messages.push_back("%s is empty");							//empty message
	_messages.push_back("%s has been sorted alphabetically");	//sorted message (alphabetically)
	_messages.push_back("%s has been edited");					//edited message
	_messages.push_back("results of '%s':\n");					//search message
	_messages.push_back("undid previous change");				//undo message
	_messages.push_back("redid previous undo");					//redo message

	_messages.push_back("invalid command");
	_messages.push_back("text not found");
	_messages.push_back("\"%s\" is already inside. y to include; n to exclude");		//clash message
	_messages.push_back("\"%s\" cannot be found in %s");
	


}

std::string Message::chooseMessage(int index){
	addMessage();
	std::string chosenMessage = _messages[index];
	return chosenMessage;
}