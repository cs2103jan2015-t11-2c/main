//@author A0116177E
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
		Log log;

	public:
		ParserFacade();
		void init(std::string);
		
		int carryOutCommand(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);

		bool isRunProgram();
		bool isHelp(std::string);	
	
		void defaultSearchFunc(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void separateWord(DataStore &, bool &, bool &);
		void removeFrontChar(std::string &);
		void removeBackChar(std::string &);
		void readFile(std::string);
};

#endif