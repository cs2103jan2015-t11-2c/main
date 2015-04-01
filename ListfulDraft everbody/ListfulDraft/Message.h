#pragma once
#include "Entry.h"

class Message
{
	private: 
/*		static const std::string MESSAGE_WELCOME;
		static const std::string MESSAGE_ACTION;

		static const std::string MESSAGE_ADD;
		static const std::string MESSAGE_DELETE;
		static const std::string MESSAGE_CLEAR;
		static const std::string MESSAGE_EDIT;
		static const std::string MESSAGE_SORT;
		static const std::string MESSAGE_SEARCH;
		static const std::string MESSAGE_UNDO;
		static const std::string MESSAGE_REDO;

		static const std::string ERROR_COMMAND;
		static const std::string ERROR_DELETE;
		static const std::string ERROR_ADD;
		static const std::string ERROR_SEARCH;
		static const std::string ERROR_EDIT;
		static const std::string ERROR_SORT;
		static const std::string ERROR_UNDO;
		static const std::string ERROR_REDO;

		static const std::string MESSAGE_EMPTY;*/

		std::vector <std::string> _messages;

	public:
	Message(void);
	~Message(void);

	void addMessage();
	std::string chooseMessage(int index);
};
