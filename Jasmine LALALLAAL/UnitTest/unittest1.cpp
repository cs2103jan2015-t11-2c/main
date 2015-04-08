#include "stdafx.h"
#include "CppUnitTest.h"

//@author A0115871E
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
#include "ParserFacade.cpp"

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
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string input1 = "add CS project meeting 6 apr 2015 1200-1600 MED";

			parseF.init(input1);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);

			std::string expectedSub1 = "CS project meeting";
			std::string actualSub1 = data.getData()[0].subject;
			int expectedTime1 = 1200;
			int actualTime1 = data.getData()[0].startTime;
			Assert::AreEqual(expectedSub1, actualSub1);
			Assert::AreEqual(expectedTime1, actualTime1);

			std::string input2 = "add visit grandma 5th april LOW";

			parseF.init(input2);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);
			
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

			parseF.init(input3);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);

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
			ParserFacade parseF;
			Parser parse;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string input1 = "add 6 apr 2015 1200-1600 CS project meeting MED";
			std::string input2 = "add 5/4/2015 visit grandma 1745-2135";
			std::string input3 = "add IE2100 homework 7 08/04/2015 1900-1300 HIGH";
			std::string input4 = "delete 1";

			parseF.init(input1);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);

			parseF.init(input2);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);

			parseF.init(input3);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);

			parseF.init(input4);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);

			std::string expectednewFirst = "CS project meeting";
			std::string actualnewFirst = data.getData()[0].subject;

			Assert::AreEqual(expectednewFirst, actualnewFirst);
		}
		TEST_METHOD(EditTest)
		{
			// TODO: Your test code here
			DataStore data;
			Classes listClass;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string input1 = "add CS project meeting 6 apr 2015  1200-1600 MED";
			std::string input2 = "edit 1 subject IE2130 meeting with prof";

			parseF.init(input1);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);
	
			parseF.init(input2);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);

			std::string expectedSubject = "IE2130 meeting with prof";
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
		TEST_METHOD(TimeBoundaryTest)
		{
			// TODO: Your test code here
			DataStore data;
			Classes listClass;
			ParserFacade parseF;
			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string input1 = "add 0000-2359 TY's bday 1st apr 2015";

			parseF.init(input1);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);

			int expectedStartTime = 0;
			int actualStartTime = data.getData()[0].startTime;
			int expectedEndTime = 2359;
			int actualEndTime = data.getData()[0].endTime;

			Assert::AreEqual(expectedStartTime, actualStartTime);
			Assert::AreEqual(expectedEndTime, actualEndTime);


		}
		TEST_METHOD(TimeExtremeTest)
		{
			// TODO: Your test code here
			DataStore data;
			Classes listClass;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string input1 = "add 2000-2400 FUNRUN";

			parseF.init(input1);
			parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);
			

			int expectedStartTime = 2000;
			int actualStartTime = data.getData()[0].startTime;
			int expectedEndTime = 2000;
			int actualEndTime = data.getData()[0].endTime;

			Assert::AreEqual(expectedStartTime, actualStartTime);
			Assert::AreEqual(expectedEndTime, actualEndTime);
			Assert::IsTrue(data.getData()[0].isFloat);

		}
	};
}