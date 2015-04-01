#include "stdafx.h"
#include "CppUnitTest.h"

#include "Parser.cpp"
#include "Date.cpp"
#include "Edit.cpp"
#include "FileLocation.cpp"
#include "Search.cpp"
#include "Sort.cpp"
#include "Timing.cpp"
#include "UserInterface.cpp"
#include "UserMessage.cpp"
#include "Priority.cpp"
#include "DataStore.cpp"
#include "Delete.cpp"
#include "Clear.cpp"
#include "Add.cpp"
#include "Category.cpp"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegratedTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(addAndAutoSort)
		{
			// TODO: Your test code here
			DataStore data;
			Classes listClass;
			Parser parse;
			std::ostringstream errMsg;
			errMsg << "(undo to remove add)";

			std::string input1 = "add CS project meeting 6 apr 2015  1200-1600 WORK MED";

			std::string userCommand;
			std::string userInfo;

			parse.init(input1);
			parse.separateWord(listClass, data);
			listClass.add.addContent(data, errMsg);

			std::string expected1 = "CS project meeting";
			std::string actual1 = data.getData()[0].subject;

			Assert::AreEqual(expected1, actual1);	

			std::string input2 = "add visit grandma 5th apr 2015 1745-2135";

			parse.init(input2);
			parse.separateWord(listClass, data);
			listClass.add.addContent(data, errMsg);

			std::string expected2 = "visit grandma";
			std::string actual2 = data.getData()[0].subject;

			Assert::AreEqual(expected2, actual2);	
		}
		
		TEST_METHOD(addDelete)
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
			std::string input4 = "delete index 2";

			parse.init(input1);
			parse.carryOutCommand(listClass, data, errMsg);
	
			parse.init(input2);
			parse.carryOutCommand(listClass, data, errMsg);

			parse.init(input3);
			parse.carryOutCommand(listClass, data, errMsg);

			parse.init(input4);
			parse.carryOutCommand(listClass, data, errMsg);

			std::string expectedFirst = "visit grandma";
			std::string actualFirst = data.getData()[0].subject;

			std::string expectedSecond = "IE2100 homework 7";
			std::string actualSecond = data.getData()[1].subject;

			Assert::AreEqual(expectedFirst, actualFirst);
			Assert::AreEqual(expectedSecond, actualSecond);

		}

/*TEST_METHOD(add)
		{
			DataStore data;
			Classes listClass;
			Parser parse;
			std::ostringstream errMsg;
			errMsg << "(undo to remove add)";

			std::string input1 = "add CS project meeting 6 apr 2015  1200-1600 WORK MED";
			std::string input2 = "add visit grandma 5th apr 2015 1745-2135";
			std::string input3 = "IE2100 homework 7 08/04/2015 1900-1300 WORK HIGH";

			parse.init(input1);

		//	int index = parse.carryOutCommand(listClass, data, errMsg);
	//		int expectedIndex = 0;
		//	Assert::AreEqual(expectedIndex, index);

			parse.separateWord(listClass, data);
	//		parse.determineCommand();
			Assert::IsTrue(listClass.add.addContent(data, errMsg));
			std::string expected1 = "CS project meeting";
			std::string actual1 = data.getData()[0].subject;

		//	parse.init(input2);
			//parse.determineCommand();
			//listClass.add.addContent(data, errMsg);

		//	int expectedDataSize = 1;
	//		int size =  data.getData().size();
	//	Assert::AreEqual(expectedDataSize, size);

			Assert::AreEqual(expected1, actual1);
		}*/
	};
}