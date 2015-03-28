#include "Messages.h"


Messages::Messages(void)
{
}


Messages::~Messages(void)
{
}

void Messages::addMessages(){
	_messages.push_back("added to %s: \"%s\"");
	_messages.push_back("deleted from %s: \"%s\"");
	_messages.push_back("all content deleted from %s");
	_messages.push_back("%s is empty");
	_messages.push_back("%s has been sorted alphabetically");
	_messages.push_back("%s has been edited");
	_messages.push_back("results of '%s':\n");
	_messages.push_back("undid previous change");
	_messages.push_back("redid previous undo");

	_messages.push_back("invalid command");
	_messages.push_back("text not found");
	_messages.push_back("\"%s\" is already inside. y to include; n to exclude");
	_messages.push_back("\"%s\" cannot be found in %s");
}

std::string Messages::chosenMessage(int index){
	addMessages();
	std::string chosenMessage = _messages[index];
	return chosenMessage;
}