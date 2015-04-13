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
#include "Classes.cpp"
#include "Category.cpp"
#include "ParserFacade.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		//Add test, floating, specific and seadline
		TEST_METHOD(AddScheduledTest)
		{
			// TODO: Your test code here
			DataStore data;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string buffer = "buffer";
			std::string input1 = "add CS project meeting 6 may 2015 1200-1600 MED WORK";
			
			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			std::string input2 = "add visit grandma 5th april 5.45 to 10";

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);
			
			std::string expectedSubject1 = "visit grandma";
			std::string actualSubject1 = data.getData()[0].subject;
			int expectedDay1 = 5;
			int actualDay1 = data.getData()[0].day;
			int expectedMonth1 = 4;
			int actualMonth1 = data.getData()[0].month;
			int expectedYear1 = 2015;
			int actualYear1 = data.getData()[0].year;
			int expectedStartTime1 = 1745;
			int actualStartTime1 = data.getData()[0].startTime;
			int expectedEndTime1 = 2200;
			int actualEndTime1 = data.getData()[0].endTime;
			std::string expectedCategory1 = "GENERAL ";
			std::string actualCategory1 = data.getData()[0].category;
			std::string expectedPriority1 = "LOW";
			std::string actualPriority1 = data.getData()[0].priority;

			Assert::AreEqual(expectedSubject1, actualSubject1);
			Assert::AreEqual(expectedDay1, actualDay1);
			Assert::AreEqual(expectedMonth1, actualMonth1);
			Assert::AreEqual(expectedYear1, actualYear1);
			Assert::AreEqual(expectedStartTime1, actualStartTime1);
			Assert::AreEqual(expectedEndTime1, actualEndTime1);
			Assert::AreEqual(expectedCategory1, actualCategory1);
			Assert::AreEqual(expectedPriority1, actualPriority1);

			std::string expectedSubject2 = "CS project meeting";
			std::string actualSubject2 = data.getData()[1].subject;
			int expectedDay2 = 6;
			int actualDay2 = data.getData()[1].day;
			int expectedMonth2 = 5;
			int actualMonth2 = data.getData()[1].month;
			int expectedYear2 = 2015;
			int actualYear2 = data.getData()[1].year;
			int expectedStartTime2 = 1200;
			int actualStartTime2 = data.getData()[1].startTime;
			int expectedEndTime2 = 1600;
			int actualEndTime2 = data.getData()[1].endTime;
			std::string expectedCategory2 = "WORK    ";
			std::string actualCategory2 = data.getData()[1].category;
			std::string expectedPriority2 = "MED ";
			std::string actualPriority2 = data.getData()[1].priority;

			Assert::AreEqual(expectedSubject2, actualSubject2);
			Assert::AreEqual(expectedDay2, actualDay2);
			Assert::AreEqual(expectedMonth2, actualMonth2);
			Assert::AreEqual(expectedYear2, actualYear2);
			Assert::AreEqual(expectedStartTime2, actualStartTime2);
			Assert::AreEqual(expectedEndTime2, actualEndTime2);
			Assert::AreEqual(expectedCategory2, actualCategory2);
			Assert::AreEqual(expectedPriority2, actualPriority2);
		}

		TEST_METHOD(AddFloatingTest)
		{
			// TODO: Your test code here
			DataStore data;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string buffer = "buffer";

			std::string input1 = "add call to change appointment";
			
			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			std::string expectedSubject1 = "call to change appointment";
			std::string actualSubject1 = data.getData()[0].subject;
			int actualStartTime1 = data.getData()[0].startTime;
			int actualEndTime1 = data.getData()[0].endTime;
			int actualDay1 = data.getData()[0].day;
			int actualMonth1 = data.getData()[0].month;
			int actualYear1 = data.getData()[0].year;		

			Assert::AreEqual(expectedSubject1, actualSubject1);
			Assert::AreEqual(0, actualStartTime1);
			Assert::AreEqual(0, actualEndTime1);
			Assert::AreEqual(0, actualDay1);
			Assert::AreEqual(0, actualMonth1);
			Assert::AreEqual(0, actualYear1);

			std::string input2 = "add play ball with friends HIGH 1900";

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);
			
			std::string expectedSubject2 = "play ball with friends";
			std::string actualSubject2 = data.getData()[1].subject;
			int actualStartTime2 = data.getData()[1].startTime;
			int actualEndTime2 = data.getData()[1].endTime;

			Assert::AreEqual(expectedSubject2, actualSubject2);
			Assert::AreEqual(1900, actualStartTime2);
			Assert::AreEqual(1900, actualEndTime2);

			std::string input3 = "add FUNRUN 2115-2345";

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			std::string expectedSubject3 = "FUNRUN";
			std::string actualSubject3 = data.getData()[2].subject;
			
			int actualStartTime3 = data.getData()[2].startTime;
			int actualEndTime3 = data.getData()[2].endTime;
			int actualDay3 = data.getData()[2].day;
			int actualMonth3 = data.getData()[2].month;
			int actualYear3 = data.getData()[2].year;		

			Assert::AreEqual(expectedSubject3, actualSubject3);
			Assert::AreEqual(2115, actualStartTime3);
			Assert::AreEqual(2345, actualEndTime3);
			Assert::AreEqual(0, actualDay3);
			Assert::AreEqual(0, actualMonth3);
			Assert::AreEqual(0, actualYear3);
		}		

		TEST_METHOD(AddDeadlineTest)
		{
			// TODO: Your test code here
			DataStore data;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string buffer = "buffer";
			std::string input1 = "add CS project due by 13/4 2359";
			
			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			std::string expectedSubject1 = "CS project";
			std::string actualSubject1 = data.getData()[0].subject;
			int actualDay1 = data.getData()[0].day;
			int actualMonth1 = data.getData()[0].month;
			int actualYear1 = data.getData()[0].year;
			int actualEndTime1 = data.getData()[0].endTime;
			int actualStartTime1 = data.getData()[0].startTime;

			Assert::AreEqual(expectedSubject1, actualSubject1);
			Assert::AreEqual(13, actualDay1);
			Assert::AreEqual(04, actualMonth1);
			Assert::AreEqual(2015, actualYear1);
			Assert::AreEqual(2359, actualEndTime1);
			Assert::AreEqual(2359, actualStartTime1);

			std::string input2 = "add IE2130 Project due on 16th Apr 2015";

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);
			
			std::string expectedSubject2 = "IE2130 Project";
			std::string actualSubject2 = data.getData()[1].subject;
			int actualDay2 = data.getData()[1].day;
			int actualMonth2 = data.getData()[1].month;
			int actualYear2 = data.getData()[1].year;
			int actualEndTime2 = data.getData()[1].endTime;
			int actualStartTime2 = data.getData()[1].startTime;

			Assert::AreEqual(expectedSubject2, actualSubject2);
			Assert::AreEqual(16, actualDay2);
			Assert::AreEqual(04, actualMonth2);
			Assert::AreEqual(2015, actualYear2);
			Assert::AreEqual(0, actualEndTime2);
			Assert::AreEqual(0, actualStartTime2);

			std::string input3 = "add lose weight xp by 1st jan 2016";

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			std::string expectedSubject3 = "lose weight xp";
			std::string actualSubject3 = data.getData()[2].subject;
			
			int actualDay3 = data.getData()[2].day;
			int actualMonth3 = data.getData()[2].month;
			int actualYear3 = data.getData()[2].year;
			int actualEndTime3 = data.getData()[2].endTime;
			int actualStartTime3 = data.getData()[2].startTime;

			Assert::AreEqual(expectedSubject3, actualSubject3);
			Assert::AreEqual(1, actualDay3);
			Assert::AreEqual(01, actualMonth3);
			Assert::AreEqual(2016, actualYear3);
			Assert::AreEqual(0, actualEndTime3);
			Assert::AreEqual(0, actualStartTime3);
		}		

		TEST_METHOD(DeleteSingleTest)
		{
			// TODO: Your test code here
			DataStore data;
			ParserFacade parseF;

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
			std::string input4 = "display";
			std::string input5 = "delete 1";
			std::string buffer = "buffer";

			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input5);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			std::string expectednewFirst = "CS project meeting";
			std::string actualnewFirst = data.getData()[0].subject;

			Assert::AreEqual(expectednewFirst, actualnewFirst);
		}

		TEST_METHOD(DeleteMultipleTest)
		{
			// TODO: Your test code here
			DataStore data;
			ParserFacade parseF;

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
			std::string input4 = "display";
			std::string input5 = "delete 1 2";
			std::string buffer = "buffer";

			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input5);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			std::string expectednewFirst = "IE2100 homework 7";
			std::string actualnewFirst = data.getData()[0].subject;

			Assert::AreEqual(expectednewFirst, actualnewFirst);
		}
		
		TEST_METHOD(EditSingleTest)
		{
			// TODO: Your test code here
			DataStore data;
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
			std::string input2 = "edit IE2130 meeting with prof";
			//std::string buffer = "buffer";

			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			//data.getPastActionLog().push_back(buffer);
	
			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			//data.getPastActionLog().push_back(buffer);

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
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);

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
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			

			int expectedStartTime = 2000;
			int actualStartTime = data.getData()[0].startTime;
			int expectedEndTime = 2000;
			int actualEndTime = data.getData()[0].endTime;

			Assert::AreEqual(expectedStartTime, actualStartTime);
			Assert::AreEqual(expectedEndTime, actualEndTime);
			Assert::IsTrue(data.getData()[0].isFloat);
		}

		TEST_METHOD(ClearTest)
		{
			// TODO: Your test code here
			DataStore data;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string buffer = "buffer";
			std::string input1 = "add 2000-2359 FUNRUN";
			std::string input2 = "add doctor appointment may 10th PERSONAL MED";
			std::string input3 = "add runNUS 24 aug 8.30am to 10am MED PERSONAL";
			std::string input4 = "clear";

			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			Assert::IsTrue(data.getData().empty());
		}

		TEST_METHOD(UndoTest)
		{
			// TODO: Your test code here
			DataStore data;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string buffer = "buffer";
			std::string input1 = "add CS project meeting 6 apr 2015 1200-1600 MED";
			std::string input2 = "add visit grandma 5th april 1200-1600 LOW";
			std::string input3 = "add FUNRUN  7th apr 1200-1600";
			std::string input4 = "undo";

			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);
			
			int actualSize = data.getData().size();
			int expectedSize = 2;

			Assert::AreEqual(expectedSize, actualSize);
		}

		TEST_METHOD(RedoTest)
		{
			// TODO: Your test code here
			DataStore data;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;

			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			std::string buffer = "buffer";
			std::string input1 = "add CS project meeting 6 apr 2015 1200-1600 MED";
			std::string input2 = "add visit grandma 5th april 1200-1600 LOW";
			std::string input3 = "add FUNRUN  7th apr 1300-1700";
			std::string input4 = "undo";
			std::string input5 = "redo";

			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);
			
			parseF.init(input5);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getPastActionLog().push_back(buffer);

			int actualSize = data.getData().size();
			int expectedSize = 3;

			Assert::AreEqual(expectedSize, actualSize);

			int expectedStartTime = 1300;
			int actualStartTime = data.getData()[2].startTime;
			int expectedEndTime = 1700;
			int actualEndTime = data.getData()[2].endTime;

			Assert::AreEqual(expectedStartTime, actualStartTime);
			Assert::AreEqual(expectedEndTime, actualEndTime);		
		}		
	};
}