#ifndef PARSERFACADE_H
#define PARSERFACADE_H

#include "Parser.h"

class ParserFacade {
	private:
		bool _isEnd;

		std::string _userInput;
		std::string _information;
	
		Parser _parse;

	public:
		ParserFacade();
		void init(std::string);

		bool isHelp(std::string);
		bool isRunProgram();
	
		void separateWord(Classes &, DataStore &, bool &, bool &);
		void removeFrontChar(std::string &);
		void removeBackChar(std::string &);
		void readFile(std::string);

		int carryOutCommand(Classes &, DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
};

#endif