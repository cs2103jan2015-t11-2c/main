#include "stdafx.h"
#include "CppUnitTest.h"

#include "Parser.cpp"
#include "Date.cpp"
#include "Edit.cpp"
#include "FileLocation.cpp"
#include "Search.cpp"
#include "Sort.cpp"
#include "Timing.cpp"
//#include "UserInterface.cpp"
#include "UserMessage.cpp"
#include "Priority.cpp"
#include "DataStore.cpp"
#include "Delete.cpp"
#include "Clear.cpp"
#include "Add.cpp"
#include "Display.cpp"
#include "Classes.cpp"
#include "Category.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(AddSortTest)
		{
			// TODO: Your test code here
			DataStore data;
			Classes listClass;
			Parser parse;
			std::ostringstream errMsg;
			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string input1 = "add CS project meeting 6 apr 2015 1200-1600 MED";

			parse.init(input1);
			parse.separateWord(listClass, data, pastDate, checkTime);
			listClass.add.addContent(data, errMsg, isTemp);

			std::string expectedSub1 = "CS project meeting";
			std::string actualSub1 = data.getData()[0].subject;
			int expectedTime1 = 1200;
			int actualTime1 = data.getData()[0].startTime;
			Assert::AreEqual(expectedSub1, actualSub1);
			Assert::AreEqual(expectedTime1, actualTime1);

			std::string input2 = "add visit grandma 5th april LOW";

			parse.init(input2);
			parse.separateWord(listClass, data, pastDate, checkTime);
			listClass.add.addContent(data, errMsg, isTemp);
			
			int expectedDay = 5;
			int actualDay = data.getData()[1].day;
			int expectedMonth = 4;
			int actualMonth = data.getData()[1].month;
			int expectedYear = 2015;
			int actualYear = data.getData()[1].year;

			Assert::AreEqual(expectedDay, actualDay);
			Assert::AreEqual(expectedMonth, actualMonth);
			Assert::AreEqual(expectedYear, actualYear);

			std::string input3 = "add FUNRUN";

			parse.init(input3);
			parse.separateWord(listClass, data, pastDate, checkTime);
			listClass.add.addContent(data, errMsg, isTemp);

			std::string expectedSub2 = "FUNRUN";
			std::string actualSub2 = data.getData()[0].subject;
			
			int actualTime2 = data.getData()[0].startTime;
			int actualDay2 = data.getData()[0].day;
			int actualMonth2 = data.getData()[0].month;
			int actualYear2 = data.getData()[0].year;

			Assert::AreEqual(expectedSub2, actualSub2);
			Assert::AreEqual(0, actualTime2);
			Assert::AreEqual(0, actualDay2);
			Assert::AreEqual(0, actualMonth2);
			Assert::AreEqual(0, actualYear2);

		}
		
		TEST_METHOD(DeleteTest)
		{
			// TODO: Your test code here
			DataStore data;
			Classes listClass;
			Parser parse;
			std::ostringstream errMsg;
			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string input1 = "add 6 apr 2015 1200-1600 CS project meeting MED";
			std::string input2 = "add 5/4/2015 visit grandma 1745-2135";
			std::string input3 = "add IE2100 homework 7 08/04/2015 1900-1300 HIGH";
			std::string input4 = "delete 1";

			parse.init(input1);
			parse.separateWord(listClass, data, pastDate, checkTime);
			listClass.add.addContent(data, errMsg, isTemp);		

			parse.init(input2);
			parse.separateWord(listClass, data, pastDate, checkTime);
			listClass.add.addContent(data, errMsg, isTemp);

			parse.init(input3);
			parse.separateWord(listClass, data, pastDate, checkTime);
			listClass.add.addContent(data, errMsg, isTemp);

			parse.init(input4);
			parse.separateWord(listClass, data, pastDate, checkTime);
			listClass.remove.deleteContent(data, parse.getInfo(), errMsg, isDelete);

			std::string expectednewFirst = "CS project meeting";
			std::string actualnewFirst = data.getData()[0].subject;

			Assert::AreEqual(expectednewFirst, actualnewFirst);
		}
		/*TEST_METHOD(addEdit)
		{
			// TODO: Your test code here
			DataStore data;
			Classes listClass;
			Parser parse;
			std::ostringstream errMsg;
			errMsg << "(undo to remove add)";

			std::string input1 = "add CS project meeting 6 apr 2015  1200-1600 WORK MED";
			std::string input2 = "edit 1 subject IE2130 project meeting";

			parse.init(input1);
			parse.carryOutCommand(listClass, data, errMsg);
	
			parse.init(input2);
			parse.carryOutCommand(listClass, data, errMsg);

			std::string expectedSubject = "IE2130 project meeting";
			std::string actualSubject = data.getData()[0].subject;

			Assert::AreEqual(expectedSubject, actualSubject);

			std::string actualDate = std::to_string(data.getData()[0].day) + "/" 
								   + std::to_string(data.getData()[0].month) + "/"
								   + std::to_string(data.getData()[0].year);
			std::string expectedDate = "6/4/2015";

			std::string expectedTime = "1200-1600";
			std::string actualTime = std::to_string(data.getData()[0].startTime) + "-" + std::to_string(data.getData()[0].endTime);

			Assert::AreEqual(expectedSubject, actualSubject);
			Assert::AreEqual(expectedDate, actualDate);
			Assert::AreEqual(expectedTime, actualTime);

		}
*/
	};
}