#ifndef PARSERFACADE_H
#define PARSERFACADE_H

#include "Parser.h"

class ParserFacade {
	private:
		bool _isRun;

		std::string _userInput;
		std::string _information;
		
		Classes listClass;
		Parser _parse;

	public:
		ParserFacade();
		void init(std::string);
		
		int carryOutCommand(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);

		bool isHelp(std::string);
		bool isRunProgram();
	
		void defaultSearchFunc(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void separateWord(DataStore &, bool &, bool &);
		void removeFrontChar(std::string &);
		void removeBackChar(std::string &);
		void readFile(std::string);
};

#endif