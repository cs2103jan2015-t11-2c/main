// Jasmine Quah Xue Li 
// Matriculation no. : A0116177E
// CE2 - TextBuddy

/**
* This class creates a text file used to store and edit the text information that the user inputs
* The user interacts with the program through typing commands and the required information
* There is no storage limit for the amount of data that can be added
* The commands are limited to: add delete clear display exit 
* In the case of duplicate information, the user is given a choice to include or exclude it
* The command format is given by the example interaction below:

	c:> TextBuddy.exe mytextfile.txt 
	Welcome to TextBuddy. mytextfile.txt is ready for use
	command: add little brown fox
	added to mytextfile.txt: “little brown fox”
	command: display
	1. little brown fox
	command: add jumped over the moon
	added to mytextfile.txt: “jumped over the moon”
	command: display
	1. little brown fox
	2. jumped over the moon
	command: delete 2
	deleted from mytextfile.txt: “jumped over the moon”
	command: display
	1. little brown fox
	command: clear
	all content deleted from mytextfile.txt
	command: display
	mytextfile.txt is empty
	command: exit

* @author Jasmine Quah
**/

#ifndef TEXTBUDDY_H
#define TEXTBUDDY_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>

class TextBuddy {
	private:
		//This vector will store the text information and will be updated after every command
		std::vector <std::string> file;

		//This vector will be used to store all search items and will be cleared after printing
		//out the results
		std::vector <std::string> tempItems;

		//This variable will create a text file with a name of the user's choice which will be 
		//updated after every command read in
		std::ofstream writeFile;

		//This variable will de used to display the created text file (if the file is created)
		std::ifstream readFile;

		//This string will store the input commands
		std::string inputCommand;

		//This variable will be used to store the index of the information that the user wants 
		//to delete
		int contentIndex;

		//This enumerator contains all possible commands
		enum commandType {
			ADD, DELETE, DISPLAY, CLEAR, SORT, SEARCH, EXIT, INVALID
		};

		//This variable will contain the identified command
		int command;

		//This variable will be used to form the output sentences
		char messageToUser[200];

		//Command messages
		static const std::string MESSAGE_ADD;
		static const std::string MESSAGE_DELETE;
		static const std::string MESSAGE_CLEAR;
		static const std::string MESSAGE_EMPTY;
		static const std::string MESSAGE_SORT;

		//Welcome message
		static const std::string MESSAGE_WELCOME;

		//Error messages
		static const std::string ERROR_COMMAND;
		static const std::string ERROR_DELETE;
		static const std::string ERROR_ADD;
		static const std::string ERROR_SEARCH;

		//Index of created text file name
		static const int FILE_INDEX;

	public:
		TextBuddy() {};
		void getCommand();
		int determineCommand();
		void checkFileCreated(std::string &);
		void carryOutCommand(std::string &);
		std::string removeWhitespace();
		void printContent(std::string &);
		void addContent(std::string &, std::string);
		bool isDuplicate(std::string &);
		void deleteContent(std::string &);
		void clearFile(std::string &);
		void compareLineSize(std::string &, std::string &, std::string &);
		bool compareWord(std::string &, std::string &, std::string &);
		void sortFile(std::string);
		void switchPlaces(int &, int &);
		void searchFile(std::string &, std::string);
		bool foundContent(std::string &);
		void output(std::string);
		void updateText(std::string &);
		bool isFileEmpty(std::string &);
		~TextBuddy() {
			while (!file.empty()) {
				file.pop_back();
			}

			while (!tempItems.empty()) {
				tempItems.pop_back();
			}
		};
		
		std::vector <std::string> getFile();
		std::vector <std::string> getTempFile();
};

#endif