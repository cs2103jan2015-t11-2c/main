#pragma once

#include "UserInterface.h"


UserInterface::UserInterface(void)
{
}


UserInterface::~UserInterface(void)
{
}

std::string UserInterface::runProgram(std::string inputLine){
	std::vector <std::string> myVec;
	std::string entryAdded;
	myVec.push_back(inputLine);
	
	return entryAdded += inputLine + " added";

}

std::string UserInterface::qotd(){
	Quotes qotd;
	return qotd.quoteOfTheDay();
}