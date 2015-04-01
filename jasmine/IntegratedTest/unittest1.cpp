#include "stdafx.h"
#include "CppUnitTest.h"
#include "Add.cpp"
#include "Category.cpp"
#include "Classes.h"
#include "Clear.cpp"
#include "Date.cpp"
#include "DataStore.cpp"
#include "Delete.cpp"
#include "Parser.cpp"
#include "Edit.cpp"
#include "Entry.h"
#include "FileLocation.cpp"
#include "Priority.cpp"
#include "Search.cpp"
#include "Sort.cpp"
#include "Timing.cpp"
#include "UserInterface.cpp"
#include "UserMessage.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegratedTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(AddDelete1)
		{
			// TODO: Your test code here
			DataStore data;
			Classes listClass;
			Parser parse;
			std::ostringstream errMsg;
			errMsg << "(undo to remove add)";

			std::string input1 = "add CS project meeting 6 apr 2015  1200-1600 WORK MED";
			std::string input2 = "add visit grandma 5th apr 2015 1745-2135";
			std::string input3 = "IE2100 homework 7 08/04/2015 1900-1300 WORK HIGH";

			parse.init(input1);
			parse.determineCommand();
			listClass.add.addContent(data, errMsg);
			std::string expected1 = "cs project meeting";
			std::string actual1 = data.getData()[1].subject;

			parse.init(input2);
			parse.determineCommand();
			listClass.add.addContent(data, errMsg);

			Assert::AreEqual(expected1, actual1);

		}

	};
}