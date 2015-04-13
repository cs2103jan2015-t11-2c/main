#include "stdafx.h"
#include "CppUnitTest.h"

//@author A0115871E
#include "Parser.cpp"
#include "Log.cpp"
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

namespace ListFulTest {		
	//@author A0116177E

	TEST_CLASS(ListFulAddTest) {
	public:
		//Test for adding a task with two timings
		//Time: 1200-1600; 12 pm-4 pm; 12 - 4; 1200 - 1600; 12pm - 4pm; 12.00 pm-4.00 pm; 12:00 - 4:00; 12-4; 12 to 4; 12 - 4; 12pm to 4
		//Date: 6 aug 2015; 6th aug; 6/8/15; 6/8/2015; 6/8; 6aug, aug6, 6aug2015, 6 August, 6 Aug
		TEST_METHOD(AddScheduledTest) {
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

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;
			int actualOutputInt4 = 0;
			int actualOutputInt5 = 0;
			int actualOutputInt6 = 0;
			int actualOutputInt7 = 0;
			int actualOutputInt8 = 0;
			int actualOutputInt9 = 0;
			int actualOutputInt10 = 0;

			std::string buffer = "buffer";
			std::string input1 = "add CS project meeting on 6 aug 2015 at 1200-1600 MED WORK";
			std::string input2 = "add MED CS project meeting on 6th aug at 12 - 4 WORK";
			std::string input3 = "add CS project meeting on at 12 pm-4 pm 6/8/15 MED WORK";
			std::string input4 = "add on 6aug CS project meeting  at 1200 - 1600 MED WORK";
			std::string input5 = "add at 12pm - 4pm MED CS project meeting 6/8 WORK";
			std::string input6 = "add CS project meeting on at 12.00 pm-4.00 pm 6aug2015 MED WORK";
			std::string input7 = "add WORK at 12:00 - 4:00 MED CS project meeting aug6";
			std::string input8 = "add CS project meeting WORK at 12-4 6/8/2015 MED";
			std::string input9 = "add WORK 6 August at 12 to 4 MED CS project meeting ";
			std::string input10 = "add CS project meeting WORK at from 12pm to 4 6 Aug MED";
			
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			actualOutputInt4 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input5);
			actualOutputInt5 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input6);
			actualOutputInt6 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input7);
			actualOutputInt7 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input8);
			actualOutputInt8 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input9);
			actualOutputInt9 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input10);
			actualOutputInt10 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
			std::string expectedSubject1 = "CS project meeting";
			std::string actualSubject1 = data.getData()[0].subject;
			
			int expectedDay1 = 6;
			int actualDay1 = data.getData()[0].day;
			int expectedMonth1 = 8;
			int actualMonth1 = data.getData()[0].month;
			int expectedYear1 = 2015;
			int actualYear1 = data.getData()[0].year;
			int expectedStartTime1 = 1200;
			int actualStartTime1 = data.getData()[0].startTime;
			int expectedEndTime1 = 1600;
			int actualEndTime1 = data.getData()[0].endTime;
			int extectedOutputInt = 0;
			std::string expectedCategory1 = "WORK    ";
			std::string actualCategory1 = data.getData()[0].category;
			std::string expectedPriority1 = "MED ";
			std::string actualPriority1 = data.getData()[0].priority;
			
			Assert::IsFalse(data.getData()[0].isFloat);
			Assert::IsTrue(data.getData()[0].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(expectedSubject1, actualSubject1);
			Assert::AreEqual(expectedDay1, actualDay1);
			Assert::AreEqual(expectedMonth1, actualMonth1);
			Assert::AreEqual(expectedYear1, actualYear1);
			Assert::AreEqual(expectedStartTime1, actualStartTime1);
			Assert::AreEqual(expectedEndTime1, actualEndTime1);
			Assert::AreEqual(expectedCategory1, actualCategory1);
			Assert::AreEqual(expectedPriority1, actualPriority1);

			std::string actualSubject2 = data.getData()[1].subject;
			
			int actualDay2 = data.getData()[1].day;
			int actualMonth2 = data.getData()[1].month;
			int actualYear2 = data.getData()[1].year;
			int actualStartTime2 = data.getData()[1].startTime;
			int actualEndTime2 = data.getData()[1].endTime;
			std::string actualCategory2 = data.getData()[1].category;
			std::string actualPriority2 = data.getData()[1].priority;
			
			Assert::IsFalse(data.getData()[1].isFloat);
			Assert::IsTrue(data.getData()[1].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt2);
			Assert::AreEqual(expectedSubject1, actualSubject2);
			Assert::AreEqual(expectedDay1, actualDay2);
			Assert::AreEqual(expectedMonth1, actualMonth2);
			Assert::AreEqual(expectedYear1, actualYear2);
			Assert::AreEqual(expectedStartTime1, actualStartTime2);
			Assert::AreEqual(expectedEndTime1, actualEndTime2);
			Assert::AreEqual(expectedCategory1, actualCategory2);
			Assert::AreEqual(expectedPriority1, actualPriority2);

			std::string actualSubject3 = data.getData()[2].subject;
			
			int actualDay3 = data.getData()[2].day;
			int actualMonth3 = data.getData()[2].month;
			int actualYear3 = data.getData()[2].year;
			int actualStartTime3 = data.getData()[2].startTime;
			int actualEndTime3 = data.getData()[2].endTime;
			std::string actualCategory3 = data.getData()[2].category;
			std::string actualPriority3 = data.getData()[2].priority;
			
			Assert::IsFalse(data.getData()[2].isFloat);
			Assert::IsTrue(data.getData()[2].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(expectedSubject1, actualSubject3);
			Assert::AreEqual(expectedDay1, actualDay3);
			Assert::AreEqual(expectedMonth1, actualMonth3);
			Assert::AreEqual(expectedYear1, actualYear3);
			Assert::AreEqual(expectedStartTime1, actualStartTime3);
			Assert::AreEqual(expectedEndTime1, actualEndTime3);
			Assert::AreEqual(expectedCategory1, actualCategory3);
			Assert::AreEqual(expectedPriority1, actualPriority3);

			std::string actualSubject4 = data.getData()[3].subject;
			
			int actualDay4 = data.getData()[3].day;
			int actualMonth4 = data.getData()[3].month;
			int actualYear4 = data.getData()[3].year;
			int actualStartTime4 = data.getData()[3].startTime;
			int actualEndTime4 = data.getData()[3].endTime;
			std::string actualCategory4 = data.getData()[3].category;
			std::string actualPriority4 = data.getData()[3].priority;
			
			Assert::IsFalse(data.getData()[3].isFloat);
			Assert::IsTrue(data.getData()[3].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt4);
			Assert::AreEqual(expectedSubject1, actualSubject4);
			Assert::AreEqual(expectedDay1, actualDay4);
			Assert::AreEqual(expectedMonth1, actualMonth4);
			Assert::AreEqual(expectedYear1, actualYear4);
			Assert::AreEqual(expectedStartTime1, actualStartTime4);
			Assert::AreEqual(expectedEndTime1, actualEndTime4);
			Assert::AreEqual(expectedCategory1, actualCategory4);
			Assert::AreEqual(expectedPriority1, actualPriority4);

			std::string actualSubject5 = data.getData()[4].subject;
			
			int actualDay5 = data.getData()[4].day;
			int actualMonth5 = data.getData()[4].month;
			int actualYear5 = data.getData()[4].year;
			int actualStartTime5 = data.getData()[2].startTime;
			int actualEndTime5 = data.getData()[4].endTime;
			std::string actualCategory5 = data.getData()[4].category;
			std::string actualPriority5 = data.getData()[4].priority;
			
			Assert::IsFalse(data.getData()[4].isFloat);
			Assert::IsTrue(data.getData()[4].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt5);
			Assert::AreEqual(expectedSubject1, actualSubject5);
			Assert::AreEqual(expectedDay1, actualDay5);
			Assert::AreEqual(expectedMonth1, actualMonth5);
			Assert::AreEqual(expectedYear1, actualYear5);
			Assert::AreEqual(expectedStartTime1, actualStartTime5);
			Assert::AreEqual(expectedEndTime1, actualEndTime5);
			Assert::AreEqual(expectedCategory1, actualCategory5);
			Assert::AreEqual(expectedPriority1, actualPriority5);

			std::string actualSubject6 = data.getData()[5].subject;
			
			int actualDay6 = data.getData()[5].day;
			int actualMonth6 = data.getData()[5].month;
			int actualYear6 = data.getData()[5].year;
			int actualStartTime6 = data.getData()[5].startTime;
			int actualEndTime6 = data.getData()[5].endTime;
			std::string actualCategory6 = data.getData()[5].category;
			std::string actualPriority6 = data.getData()[5].priority;
			
			Assert::IsFalse(data.getData()[5].isFloat);
			Assert::IsTrue(data.getData()[5].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt6);
			Assert::AreEqual(expectedSubject1, actualSubject6);
			Assert::AreEqual(expectedDay1, actualDay6);
			Assert::AreEqual(expectedMonth1, actualMonth6);
			Assert::AreEqual(expectedYear1, actualYear6);
			Assert::AreEqual(expectedStartTime1, actualStartTime6);
			Assert::AreEqual(expectedEndTime1, actualEndTime6);
			Assert::AreEqual(expectedCategory1, actualCategory6);
			Assert::AreEqual(expectedPriority1, actualPriority6);

			std::string actualSubject7 = data.getData()[6].subject;
			
			int actualDay7 = data.getData()[6].day;
			int actualMonth7 = data.getData()[6].month;
			int actualYear7 = data.getData()[6].year;
			int actualStartTime7 = data.getData()[6].startTime;
			int actualEndTime7= data.getData()[6].endTime;
			std::string actualCategory7 = data.getData()[6].category;
			std::string actualPriority7 = data.getData()[6].priority;
			
			Assert::IsFalse(data.getData()[6].isFloat);
			Assert::IsTrue(data.getData()[6].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt7);
			Assert::AreEqual(expectedSubject1, actualSubject7);
			Assert::AreEqual(expectedDay1, actualDay7);
			Assert::AreEqual(expectedMonth1, actualMonth7);
			Assert::AreEqual(expectedYear1, actualYear7);
			Assert::AreEqual(expectedStartTime1, actualStartTime7);
			Assert::AreEqual(expectedEndTime1, actualEndTime7);
			Assert::AreEqual(expectedCategory1, actualCategory7);
			Assert::AreEqual(expectedPriority1, actualPriority7);

			std::string actualSubject8 = data.getData()[7].subject;
			
			int actualDay8 = data.getData()[7].day;
			int actualMonth8 = data.getData()[7].month;
			int actualYear8 = data.getData()[7].year;
			int actualStartTime8 = data.getData()[7].startTime;
			int actualEndTime8 = data.getData()[7].endTime;
			std::string actualCategory8 = data.getData()[7].category;
			std::string actualPriority8 = data.getData()[7].priority;
			
			Assert::IsFalse(data.getData()[7].isFloat);
			Assert::IsTrue(data.getData()[7].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt8);
			Assert::AreEqual(expectedSubject1, actualSubject8);
			Assert::AreEqual(expectedDay1, actualDay8);
			Assert::AreEqual(expectedMonth1, actualMonth8);
			Assert::AreEqual(expectedYear1, actualYear8);
			Assert::AreEqual(expectedStartTime1, actualStartTime8);
			Assert::AreEqual(expectedEndTime1, actualEndTime8);
			Assert::AreEqual(expectedCategory1, actualCategory8);
			Assert::AreEqual(expectedPriority1, actualPriority8);

			std::string actualSubject9 = data.getData()[8].subject;
			
			int actualDay9 = data.getData()[8].day;
			int actualMonth9 = data.getData()[8].month;
			int actualYear9 = data.getData()[8].year;
			int actualStartTime9 = data.getData()[8].startTime;
			int actualEndTime9 = data.getData()[8].endTime;
			std::string actualCategory9 = data.getData()[8].category;
			std::string actualPriority9 = data.getData()[8].priority;
			
			Assert::IsFalse(data.getData()[8].isFloat);
			Assert::IsTrue(data.getData()[8].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt9);
			Assert::AreEqual(expectedSubject1, actualSubject9);
			Assert::AreEqual(expectedDay1, actualDay9);
			Assert::AreEqual(expectedMonth1, actualMonth9);
			Assert::AreEqual(expectedYear1, actualYear9);
			Assert::AreEqual(expectedStartTime1, actualStartTime9);
			Assert::AreEqual(expectedEndTime1, actualEndTime9);
			Assert::AreEqual(expectedCategory1, actualCategory9);
			Assert::AreEqual(expectedPriority1, actualPriority9);

			std::string actualSubject10 = data.getData()[9].subject;
			
			int actualDay10 = data.getData()[9].day;
			int actualMonth10 = data.getData()[9].month;
			int actualYear10 = data.getData()[9].year;
			int actualStartTime10 = data.getData()[9].startTime;
			int actualEndTime10 = data.getData()[9].endTime;
			std::string actualCategory10 = data.getData()[9].category;
			std::string actualPriority10 = data.getData()[9].priority;
			
			Assert::IsFalse(data.getData()[9].isFloat);
			Assert::IsTrue(data.getData()[9].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt10);
			Assert::AreEqual(expectedSubject1, actualSubject10);
			Assert::AreEqual(expectedDay1, actualDay10);
			Assert::AreEqual(expectedMonth1, actualMonth10);
			Assert::AreEqual(expectedYear1, actualYear10);
			Assert::AreEqual(expectedStartTime1, actualStartTime10);
			Assert::AreEqual(expectedEndTime1, actualEndTime10);
			Assert::AreEqual(expectedCategory1, actualCategory10);
			Assert::AreEqual(expectedPriority1, actualPriority10);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 10;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}

		//Test for adding a task with one timings with different formats
		//Date: 'tmr'; 'tomoro'; 'tomorrow'
		//Date: 'tdy'; 'today'; 'later'; 'tonight'
		//Time: 6:00, 6pm, 6 pm
		TEST_METHOD(AddDeadlineTest) {
			DataStore data;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;
			
			time_t t = time(0);   
			struct tm now;
			localtime_s(&now, &t);
			
			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;
			int actualOutputInt4 = 0;
			int actualOutputInt5 = 0;
			int actualOutputInt6 = 0;
			int actualOutputInt7 = 0;

			//tmr
			std::string buffer = "buffer";
			std::string input1 = "add MED PERSONAL play football with neighbours at 6pm tmr";
			std::string input2 = "add PERSONAL tomoro play football with neighbours at 6:00  MED";
			std::string input3 = "add tomorrow PERSONAL play football with neighbours MED at 6 pm";
			//today
			std::string input4 = "add MED PERSONAL play football with neighbours at 6pm tdy";
			std::string input5 = "add PERSONAL today play football with neighbours at 6:00  MED";
			std::string input6 = "add later PERSONAL play football with neighbours MED at 6 pm";
			std::string input7 = "add PERSONAL play football with neighbours tonight MED at 6 pm";
			
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			actualOutputInt4 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input5);
			actualOutputInt5 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input6);
			actualOutputInt6 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input7);
			actualOutputInt7 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
			std::string expectedSubject1 = "play football with neighbours";
			std::string actualSubject1 = data.getData()[0].subject;
			
			int expectedDay1 = now.tm_mday + 1;
			int expectedDay2 = now.tm_mday;

			int actualDay1 = data.getData()[0].day;
			int expectedMonth1 = (now.tm_mon + 1);
			int actualMonth1 = data.getData()[0].month;
			int expectedYear1 = (now.tm_year + 1900);
			int actualYear1 = data.getData()[0].year;
			int expectedStartTime1 = 1800;
			int actualStartTime1 = data.getData()[0].startTime;
			int expectedEndTime1 = 1800;
			int actualEndTime1 = data.getData()[0].endTime;
			int extectedOutputInt = 0;
			std::string expectedCategory1 = "PERSONAL";
			std::string actualCategory1 = data.getData()[0].category;
			std::string expectedPriority1 = "MED ";
			std::string actualPriority1 = data.getData()[0].priority;

			Assert::IsFalse(data.getData()[0].isFloat);
			Assert::IsFalse(data.getData()[0].isTimedTask);
			Assert::AreEqual(expectedSubject1, actualSubject1);
			Assert::AreEqual(expectedDay2, actualDay1);
			Assert::AreEqual(expectedMonth1, actualMonth1);
			Assert::AreEqual(expectedYear1, actualYear1);
			Assert::AreEqual(expectedStartTime1, actualStartTime1);
			Assert::AreEqual(expectedEndTime1, actualEndTime1);
			Assert::AreEqual(expectedCategory1, actualCategory1);
			Assert::AreEqual(expectedPriority1, actualPriority1);

			std::string actualSubject2 = data.getData()[1].subject;
			
			int actualDay2 = data.getData()[1].day;
			int actualMonth2 = data.getData()[1].month;
			int actualYear2 = data.getData()[1].year;
			int actualStartTime2 = data.getData()[1].startTime;
			int actualEndTime2 = data.getData()[1].endTime;
			std::string actualCategory2 = data.getData()[1].category;
			std::string actualPriority2 = data.getData()[1].priority;
			
			Assert::IsFalse(data.getData()[1].isFloat);
			Assert::IsFalse(data.getData()[1].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt2);
			Assert::AreEqual(expectedSubject1, actualSubject2);
			Assert::AreEqual(expectedDay2, actualDay2);
			Assert::AreEqual(expectedMonth1, actualMonth2);
			Assert::AreEqual(expectedYear1, actualYear2);
			Assert::AreEqual(expectedStartTime1, actualStartTime2);
			Assert::AreEqual(expectedEndTime1, actualEndTime2);
			Assert::AreEqual(expectedCategory1, actualCategory2);
			Assert::AreEqual(expectedPriority1, actualPriority2);

			std::string actualSubject3 = data.getData()[2].subject;
			
			int actualDay3 = data.getData()[2].day;
			int actualMonth3 = data.getData()[2].month;
			int actualYear3 = data.getData()[2].year;
			int actualStartTime3 = data.getData()[2].startTime;
			int actualEndTime3 = data.getData()[2].endTime;
			std::string actualCategory3 = data.getData()[2].category;
			std::string actualPriority3 = data.getData()[2].priority;
			
			Assert::IsFalse(data.getData()[2].isFloat);
			Assert::IsFalse(data.getData()[2].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(expectedSubject1, actualSubject3);
			Assert::AreEqual(expectedDay2, actualDay3);
			Assert::AreEqual(expectedMonth1, actualMonth3);
			Assert::AreEqual(expectedYear1, actualYear3);
			Assert::AreEqual(expectedStartTime1, actualStartTime3);
			Assert::AreEqual(expectedEndTime1, actualEndTime3);
			Assert::AreEqual(expectedCategory1, actualCategory3);
			Assert::AreEqual(expectedPriority1, actualPriority3);

			std::string actualSubject4 = data.getData()[3].subject;
			
			int actualDay4 = data.getData()[3].day;
			int actualMonth4 = data.getData()[3].month;
			int actualYear4 = data.getData()[3].year;
			int actualStartTime4 = data.getData()[3].startTime;
			int actualEndTime4 = data.getData()[3].endTime;
			std::string actualCategory4 = data.getData()[3].category;
			std::string actualPriority4 = data.getData()[3].priority;
			
			Assert::IsFalse(data.getData()[3].isFloat);
			Assert::IsFalse(data.getData()[3].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt4);
			Assert::AreEqual(expectedSubject1, actualSubject4);
			Assert::AreEqual(expectedDay2, actualDay4);
			Assert::AreEqual(expectedMonth1, actualMonth4);
			Assert::AreEqual(expectedYear1, actualYear4);
			Assert::AreEqual(expectedStartTime1, actualStartTime4);
			Assert::AreEqual(expectedEndTime1, actualEndTime4);
			Assert::AreEqual(expectedCategory1, actualCategory4);
			Assert::AreEqual(expectedPriority1, actualPriority4);

			std::string actualSubject5 = data.getData()[4].subject;
			
			int actualDay5 = data.getData()[4].day;
			int actualMonth5 = data.getData()[4].month;
			int actualYear5 = data.getData()[4].year;
			int actualStartTime5 = data.getData()[4].startTime;
			int actualEndTime5 = data.getData()[4].endTime;
			std::string actualCategory5 = data.getData()[4].category;
			std::string actualPriority5 = data.getData()[4].priority;
			
			Assert::IsFalse(data.getData()[4].isFloat);
			Assert::IsFalse(data.getData()[4].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt5);
			Assert::AreEqual(expectedSubject1, actualSubject5);
			Assert::AreEqual(expectedDay1, actualDay5);
			Assert::AreEqual(expectedMonth1, actualMonth5);
			Assert::AreEqual(expectedYear1, actualYear5);
			Assert::AreEqual(expectedStartTime1, actualStartTime5);
			Assert::AreEqual(expectedEndTime1, actualEndTime5);
			Assert::AreEqual(expectedCategory1, actualCategory5);
			Assert::AreEqual(expectedPriority1, actualPriority5);

			std::string actualSubject6 = data.getData()[5].subject;
			
			int actualDay6 = data.getData()[5].day;
			int actualMonth6 = data.getData()[5].month;
			int actualYear6 = data.getData()[5].year;
			int actualStartTime6 = data.getData()[5].startTime;
			int actualEndTime6 = data.getData()[5].endTime;
			std::string actualCategory6 = data.getData()[5].category;
			std::string actualPriority6 = data.getData()[5].priority;
			
			Assert::IsFalse(data.getData()[5].isFloat);
			Assert::IsFalse(data.getData()[5].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt6);
			Assert::AreEqual(expectedSubject1, actualSubject6);
			Assert::AreEqual(expectedDay1, actualDay6);
			Assert::AreEqual(expectedMonth1, actualMonth6);
			Assert::AreEqual(expectedYear1, actualYear6);
			Assert::AreEqual(expectedStartTime1, actualStartTime6);
			Assert::AreEqual(expectedEndTime1, actualEndTime6);
			Assert::AreEqual(expectedCategory1, actualCategory6);
			Assert::AreEqual(expectedPriority1, actualPriority6);

			std::string actualSubject7 = data.getData()[6].subject;
			
			int actualDay7 = data.getData()[6].day;
			int actualMonth7 = data.getData()[6].month;
			int actualYear7 = data.getData()[6].year;
			int actualStartTime7 = data.getData()[6].startTime;
			int actualEndTime7= data.getData()[6].endTime;
			std::string actualCategory7 = data.getData()[6].category;
			std::string actualPriority7 = data.getData()[6].priority;
			
			Assert::IsFalse(data.getData()[6].isFloat);
			Assert::IsFalse(data.getData()[6].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt7);
			Assert::AreEqual(expectedSubject1, actualSubject7);
			Assert::AreEqual(expectedDay1, actualDay7);
			Assert::AreEqual(expectedMonth1, actualMonth7);
			Assert::AreEqual(expectedYear1, actualYear7);
			Assert::AreEqual(expectedStartTime1, actualStartTime7);
			Assert::AreEqual(expectedEndTime1, actualEndTime7);
			Assert::AreEqual(expectedCategory1, actualCategory7);
			Assert::AreEqual(expectedPriority1, actualPriority7);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 7;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}

		//Test for adding floating tasks with different formats
		//Time: 0630 am; 6.30am; 6:30 am
		TEST_METHOD(AddFloatingTest) {
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

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;

			std::string buffer = "buffer";
			std::string input1 = "add LOW taiji session at 6.30am onwards PERSONAL";
			std::string input2 = "add taiji session PERSONAL 0630 am LOW";
			std::string input3 = "add 6:30 am LOW taiji session PERSONAL";
			
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
		
			std::string expectedSubject1 = "taiji session";
			std::string actualSubject1 = data.getData()[0].subject;
			
			int expectedDay1 = 0;
			int actualDay1 = data.getData()[0].day;
			int expectedMonth1 = 0;
			int actualMonth1 = data.getData()[0].month;
			int expectedYear1 = 0;
			int actualYear1 = data.getData()[0].year;
			int expectedStartTime1 = 630;
			int actualStartTime1 = data.getData()[0].startTime;
			int expectedEndTime1 = 630;
			int actualEndTime1 = data.getData()[0].endTime;
			int extectedOutputInt = 0;
			std::string expectedCategory1 = "PERSONAL";
			std::string actualCategory1 = data.getData()[0].category;
			std::string expectedPriority1 = "LOW ";
			std::string actualPriority1 = data.getData()[0].priority;
			
			Assert::IsTrue(data.getData()[0].isFloat);
			Assert::IsFalse(data.getData()[0].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(expectedSubject1, actualSubject1);
			Assert::AreEqual(expectedDay1, actualDay1);
			Assert::AreEqual(expectedMonth1, actualMonth1);
			Assert::AreEqual(expectedYear1, actualYear1);
			Assert::AreEqual(expectedStartTime1, actualStartTime1);
			Assert::AreEqual(expectedEndTime1, actualEndTime1);
			Assert::AreEqual(expectedCategory1, actualCategory1);
			Assert::AreEqual(expectedPriority1, actualPriority1);
	
			std::string actualSubject2 = data.getData()[1].subject;
			
			int actualDay2 = data.getData()[1].day;
			int actualMonth2 = data.getData()[1].month;
			int actualYear2 = data.getData()[1].year;
			int actualStartTime2 = data.getData()[1].startTime;
			int actualEndTime2 = data.getData()[1].endTime;
			std::string actualCategory2 = data.getData()[1].category;
			std::string actualPriority2 = data.getData()[1].priority;
			
			Assert::IsTrue(data.getData()[1].isFloat);
			Assert::IsFalse(data.getData()[1].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt2);
			Assert::AreEqual(expectedSubject1, actualSubject2);
			Assert::AreEqual(expectedDay1, actualDay2);
			Assert::AreEqual(expectedMonth1, actualMonth2);
			Assert::AreEqual(expectedYear1, actualYear2);
			Assert::AreEqual(expectedStartTime1, actualStartTime2);
			Assert::AreEqual(expectedEndTime1, actualEndTime2);
			Assert::AreEqual(expectedCategory1, actualCategory2);
			Assert::AreEqual(expectedPriority1, actualPriority2);

			std::string actualSubject3 = data.getData()[2].subject;
			
			int actualDay3 = data.getData()[2].day;
			int actualMonth3 = data.getData()[2].month;
			int actualYear3 = data.getData()[2].year;
			int actualStartTime3 = data.getData()[2].startTime;
			int actualEndTime3 = data.getData()[2].endTime;
			std::string actualCategory3 = data.getData()[2].category;
			std::string actualPriority3 = data.getData()[2].priority;
			
			Assert::IsTrue(data.getData()[2].isFloat);
			Assert::IsFalse(data.getData()[2].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(expectedSubject1, actualSubject3);
			Assert::AreEqual(expectedDay1, actualDay3);
			Assert::AreEqual(expectedMonth1, actualMonth3);
			Assert::AreEqual(expectedYear1, actualYear3);
			Assert::AreEqual(expectedStartTime1, actualStartTime3);
			Assert::AreEqual(expectedEndTime1, actualEndTime3);
			Assert::AreEqual(expectedCategory1, actualCategory3);
			Assert::AreEqual(expectedPriority1, actualPriority3);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 3;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}

		//Test for adding by weekdays with different formats to the next week
		//Date: 'next Wed'; 'next Wednesday"; 'next wed'
		//Time: 1-4; 1300 - 1600; from 1pm to 4pm
		TEST_METHOD(AddNextWeekdayTest) {
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

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;
			
			time_t t = time(0);   
			struct tm timeInfo;
			localtime_s(&timeInfo, &t);
			const char *weekday[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
			int count = 1;
			int i = 0;
			for (;;) {
				mktime(&timeInfo);
				if (weekday[timeInfo.tm_wday] == "Wednesday") {
					if (count == 1 && i > 7) {
						break;
					}
					else if (count == 0) {
						break;
					}
				}
				timeInfo.tm_mday = timeInfo.tm_mday + 1;
				i++;
			}

			std::string buffer = "buffer";
			std::string input1 = "add PERSONAL wedding at Raffles place next Wednesday HIGH from 1pm to 4pm";
			std::string input2 = "add PERSONAL next Wed 1-4 wedding at Raffles place HIGH";
			std::string input3 = "add next wed PERSONAL wedding at Raffles place from 1300 - 1600 HIGH ";
			
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
			std::string expectedSubject1 = "wedding at Raffles place";
			std::string actualSubject1 = data.getData()[0].subject;
			
			int expectedDay1 = timeInfo.tm_mday;
			int actualDay1 = data.getData()[0].day;
			int expectedMonth1 = timeInfo.tm_mon + 1;
			int actualMonth1 = data.getData()[0].month;
			int expectedYear1 = timeInfo.tm_year + 1900;
			int actualYear1 = data.getData()[0].year;
			int expectedStartTime1 = 1300;
			int actualStartTime1 = data.getData()[0].startTime;
			int expectedEndTime1 = 1600;
			int actualEndTime1 = data.getData()[0].endTime;
			int extectedOutputInt = 0;
			std::string expectedCategory1 = "PERSONAL";
			std::string actualCategory1 = data.getData()[0].category;
			std::string expectedPriority1 = "HIGH";
			std::string actualPriority1 = data.getData()[0].priority;
			
			Assert::IsFalse(data.getData()[0].isFloat);
			Assert::IsTrue(data.getData()[0].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(expectedSubject1, actualSubject1);
			Assert::AreEqual(expectedDay1, actualDay1);
			Assert::AreEqual(expectedMonth1, actualMonth1);
			Assert::AreEqual(expectedYear1, actualYear1);
			Assert::AreEqual(expectedStartTime1, actualStartTime1);
			Assert::AreEqual(expectedEndTime1, actualEndTime1);
			Assert::AreEqual(expectedCategory1, actualCategory1);
			Assert::AreEqual(expectedPriority1, actualPriority1);

			std::string actualSubject2 = data.getData()[1].subject;
			
			int actualDay2 = data.getData()[1].day;
			int actualMonth2 = data.getData()[1].month;
			int actualYear2 = data.getData()[1].year;
			int actualStartTime2 = data.getData()[1].startTime;
			int actualEndTime2 = data.getData()[1].endTime;
			std::string actualCategory2 = data.getData()[1].category;
			std::string actualPriority2 = data.getData()[1].priority;
			
			Assert::IsFalse(data.getData()[1].isFloat);
			Assert::IsTrue(data.getData()[1].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(expectedSubject1, actualSubject2);
			Assert::AreEqual(expectedDay1, actualDay2);
			Assert::AreEqual(expectedMonth1, actualMonth2);
			Assert::AreEqual(expectedYear1, actualYear2);
			Assert::AreEqual(expectedStartTime1, actualStartTime2);
			Assert::AreEqual(expectedEndTime1, actualEndTime2);
			Assert::AreEqual(expectedCategory1, actualCategory2);
			Assert::AreEqual(expectedPriority1, actualPriority2);

			std::string actualSubject3 = data.getData()[2].subject;
			
			int actualDay3 = data.getData()[2].day;
			int actualMonth3 = data.getData()[2].month;
			int actualYear3 = data.getData()[2].year;
			int actualStartTime3 = data.getData()[2].startTime;
			int actualEndTime3 = data.getData()[2].endTime;
			std::string actualCategory3 = data.getData()[2].category;
			std::string actualPriority3 = data.getData()[2].priority;
			
			Assert::IsFalse(data.getData()[2].isFloat);
			Assert::IsTrue(data.getData()[2].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(expectedSubject1, actualSubject3);
			Assert::AreEqual(expectedDay1, actualDay3);
			Assert::AreEqual(expectedMonth1, actualMonth3);
			Assert::AreEqual(expectedYear1, actualYear3);
			Assert::AreEqual(expectedStartTime1, actualStartTime3);
			Assert::AreEqual(expectedEndTime1, actualEndTime3);
			Assert::AreEqual(expectedCategory1, actualCategory3);
			Assert::AreEqual(expectedPriority1, actualPriority3);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 3;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}

		//Test for adding by weekdays with different formats
		//Date: 'Tue'; 'tue"; 'Tuesday'; 'tuesday'
		//Time: 1-4; 1300 - 1600; from 1pm to 4pm
		TEST_METHOD(AddWeekdayTest) {
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

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;
			int actualOutputInt4 = 0;
			
			time_t t = time(0);   
			struct tm timeInfo;
			localtime_s(&timeInfo, &t);
			const char *weekday[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
			int count = 0;
			int i = 0;
			for (;;) {
				mktime(&timeInfo);
				if (weekday[timeInfo.tm_wday] == "Tuesday") {
					if (count == 1 && i > 7) {
						break;
					}
					else if (count == 0) {
						break;
					}
				}
				timeInfo.tm_mday = timeInfo.tm_mday + 1;
				i++;
			}

			std::string buffer = "buffer";
			std::string input1 = "add PERSONAL wedding at Raffles place Tue HIGH from 1pm to 4pm";
			std::string input2 = "add PERSONAL tue 1-4 wedding at Raffles place HIGH";
			std::string input3 = "add Tuesday PERSONAL wedding at Raffles place from 1300 - 1600 HIGH ";
			std::string input4 = "add wedding at Raffles place from 1300 - 1600 tuesday PERSONAL HIGH ";
			
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			actualOutputInt4 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
			std::string expectedSubject1 = "wedding at Raffles place";
			std::string actualSubject1 = data.getData()[0].subject;
			
			int expectedDay1 = timeInfo.tm_mday;
			int actualDay1 = data.getData()[0].day;
			int expectedMonth1 = timeInfo.tm_mon + 1;
			int actualMonth1 = data.getData()[0].month;
			int expectedYear1 = timeInfo.tm_year + 1900;
			int actualYear1 = data.getData()[0].year;
			int expectedStartTime1 = 1300;
			int actualStartTime1 = data.getData()[0].startTime;
			int expectedEndTime1 = 1600;
			int actualEndTime1 = data.getData()[0].endTime;
			int extectedOutputInt = 0;
			std::string expectedCategory1 = "PERSONAL";
			std::string actualCategory1 = data.getData()[0].category;
			std::string expectedPriority1 = "HIGH";
			std::string actualPriority1 = data.getData()[0].priority;
			
			Assert::IsFalse(data.getData()[0].isFloat);
			Assert::IsTrue(data.getData()[0].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(expectedSubject1, actualSubject1);
			Assert::AreEqual(expectedDay1, actualDay1);
			Assert::AreEqual(expectedMonth1, actualMonth1);
			Assert::AreEqual(expectedYear1, actualYear1);
			Assert::AreEqual(expectedStartTime1, actualStartTime1);
			Assert::AreEqual(expectedEndTime1, actualEndTime1);
			Assert::AreEqual(expectedCategory1, actualCategory1);
			Assert::AreEqual(expectedPriority1, actualPriority1);

			std::string actualSubject2 = data.getData()[1].subject;
			
			int actualDay2 = data.getData()[1].day;
			int actualMonth2 = data.getData()[1].month;
			int actualYear2 = data.getData()[1].year;
			int actualStartTime2 = data.getData()[1].startTime;
			int actualEndTime2 = data.getData()[1].endTime;
			std::string actualCategory2 = data.getData()[1].category;
			std::string actualPriority2 = data.getData()[1].priority;
			
			Assert::IsFalse(data.getData()[1].isFloat);
			Assert::IsTrue(data.getData()[1].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(expectedSubject1, actualSubject2);
			Assert::AreEqual(expectedDay1, actualDay2);
			Assert::AreEqual(expectedMonth1, actualMonth2);
			Assert::AreEqual(expectedYear1, actualYear2);
			Assert::AreEqual(expectedStartTime1, actualStartTime2);
			Assert::AreEqual(expectedEndTime1, actualEndTime2);
			Assert::AreEqual(expectedCategory1, actualCategory2);
			Assert::AreEqual(expectedPriority1, actualPriority2);

			std::string actualSubject3 = data.getData()[2].subject;
			
			int actualDay3 = data.getData()[2].day;
			int actualMonth3 = data.getData()[2].month;
			int actualYear3 = data.getData()[2].year;
			int actualStartTime3 = data.getData()[2].startTime;
			int actualEndTime3 = data.getData()[2].endTime;
			std::string actualCategory3 = data.getData()[2].category;
			std::string actualPriority3 = data.getData()[2].priority;
			
			Assert::IsFalse(data.getData()[2].isFloat);
			Assert::IsTrue(data.getData()[2].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(expectedSubject1, actualSubject3);
			Assert::AreEqual(expectedDay1, actualDay3);
			Assert::AreEqual(expectedMonth1, actualMonth3);
			Assert::AreEqual(expectedYear1, actualYear3);
			Assert::AreEqual(expectedStartTime1, actualStartTime3);
			Assert::AreEqual(expectedEndTime1, actualEndTime3);
			Assert::AreEqual(expectedCategory1, actualCategory3);
			Assert::AreEqual(expectedPriority1, actualPriority3);

			std::string actualSubject4 = data.getData()[3].subject;
			
			int actualDay4 = data.getData()[3].day;
			int actualMonth4 = data.getData()[3].month;
			int actualYear4 = data.getData()[3].year;
			int actualStartTime4 = data.getData()[3].startTime;
			int actualEndTime4 = data.getData()[3].endTime;
			std::string actualCategory4 = data.getData()[3].category;
			std::string actualPriority4 = data.getData()[3].priority;
			
			Assert::IsFalse(data.getData()[3].isFloat);
			Assert::IsTrue(data.getData()[3].isTimedTask);
			Assert::AreEqual(extectedOutputInt, actualOutputInt4);
			Assert::AreEqual(expectedSubject1, actualSubject4);
			Assert::AreEqual(expectedDay1, actualDay4);
			Assert::AreEqual(expectedMonth1, actualMonth4);
			Assert::AreEqual(expectedYear1, actualYear4);
			Assert::AreEqual(expectedStartTime1, actualStartTime4);
			Assert::AreEqual(expectedEndTime1, actualEndTime4);
			Assert::AreEqual(expectedCategory1, actualCategory4);
			Assert::AreEqual(expectedPriority1, actualPriority4);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 4;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}

		//Test for adding according to time
		TEST_METHOD(AddAccordingToTime) {
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

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;
			int actualOutputInt4 = 0;
			int actualOutputInt5 = 0;
			int actualOutputInt6 = 0;
			int actualOutputInt7 = 0;
			int actualOutputInt8 = 0;
		
			std::string buffer = "buffer";
			std::string input1 = "add b 2.30pm";
			std::string input2 = "add a 1600";
			std::string input3 = "add c 3 pm";
			std::string input4 = "add d 1pm";
				
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			actualOutputInt4 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
		
			int extectedOutputInt = 0;

			int expectedTime1 = 1300;
			int expectedTime2 = 1430;
			int expectedTime3 = 1500;
			int expectedTime4 = 1600;

			int actualTime1 = data.getData()[0].startTime;
			int actualTime2 = data.getData()[1].startTime;
			int actualTime3 = data.getData()[2].startTime;
			int actualTime4 = data.getData()[3].startTime;

			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(extectedOutputInt, actualOutputInt2);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(extectedOutputInt, actualOutputInt4);
	
			Assert::AreEqual(expectedTime1, actualTime1);
			Assert::AreEqual(expectedTime2, actualTime2);
			Assert::AreEqual(expectedTime3, actualTime3);
			Assert::AreEqual(expectedTime4, actualTime4);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 4;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}

		//Test for adding according to date
		TEST_METHOD(AddAccordingToDate) {
			DataStore data;
			ParserFacade parseF;

			std::ostringstream errMsg;
			std::ostringstream floating;
			std::ostringstream scheduled;
			std::ostringstream deadline;
			
			time_t t = time(0);   
			struct tm now;
			localtime_s(&now, &t);
			
			bool pastDate = false;
			bool checkTime = false;
			bool isTemp = false;
			bool isDelete = false;

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;
			int actualOutputInt4 = 0;
		
			std::string buffer = "buffer";
			std::string input1 = "add b tdy";
			std::string input2 = "add a 10th apr";
			std::string input3 = "add c tmr";
			std::string input4 = "add d 16 November";
				
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			actualOutputInt4 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
		
			int extectedOutputInt = 0;

			int expectedDay1 = 10;
			int expectedMonth1 = 4;
			int expectedDay2 = now.tm_mday;
			int expectedMonth2 = (now.tm_mon + 1);
			int expectedDay3 = (now.tm_mday + 1);
			int expectedMonth3 = (now.tm_mon + 1);
			int expectedDay4 = 16;
			int expectedMonth4 = 11;


			int actualDay1 = data.getData()[0].day;
			int actualDay2 = data.getData()[1].day;
			int actualDay3 = data.getData()[2].day;
			int actualDay4 = data.getData()[3].day;
			int actualMonth1 = data.getData()[0].month;
			int actualMonth2 = data.getData()[1].month;
			int actualMonth3 = data.getData()[2].month;
			int actualMonth4 = data.getData()[3].month;

			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(extectedOutputInt, actualOutputInt2);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(extectedOutputInt, actualOutputInt4);
	
			Assert::AreEqual(expectedDay1, actualDay1);
			Assert::AreEqual(expectedDay2, actualDay2);
			Assert::AreEqual(expectedDay3, actualDay3);
			Assert::AreEqual(expectedDay4, actualDay4);
			Assert::AreEqual(expectedMonth1, actualMonth1);
			Assert::AreEqual(expectedMonth2, actualMonth2);
			Assert::AreEqual(expectedMonth3, actualMonth3);
			Assert::AreEqual(expectedMonth4, actualMonth4);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 4;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}
	};
	
	//@author A0115871E
	TEST_CLASS(ListFulSortTest) {
	public:
		//Test for sorting by subject
		//According to floating, scheduled, deadline tasks
		TEST_METHOD(SortSubjectTest) {
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

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;
			int actualOutputInt4 = 0;
			int actualOutputInt5 = 0;
			int actualOutputInt6 = 0;
			int actualOutputInt7 = 0;
			int actualOutputInt8 = 0;
			int actualOutputInt9 = 0;
			int actualOutputInt10 = 0;
			
			std::string buffer = "buffer";
			std::string input1 = "add b";
			std::string input2 = "add a";
			std::string input3 = "add c";

			std::string input4 = "add c 5 may";
			std::string input5 = "add a 5/5/2015";
			std::string input6 = "add b may 5";
			
			std::string input7 = "add a 5 pm to 6pm 6aug";
			std::string input8 = "add c 6th August 2015 5:00-6:00";
			std::string input9 = "add b 6/8/15 from 5 to 6";
			
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			actualOutputInt4 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input5);
			actualOutputInt5 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input6);
			actualOutputInt6 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input7);
			actualOutputInt7 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input8);
			actualOutputInt8 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input9);
			actualOutputInt9 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
			parseF.init("sort sub");
			actualOutputInt10 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
			int extectedOutputInt = 0;
			int extectedOutputInt2 = 4;

			std::string expectedSubject1 = "a";
			std::string expectedSubject2 = "b";
			std::string expectedSubject3 = "c";

			std::string actualSubject1 = data.getData()[0].subject;
			std::string actualSubject2 = data.getData()[1].subject;
			std::string actualSubject3 = data.getData()[2].subject;
			std::string actualSubject4 = data.getData()[3].subject;
			std::string actualSubject5 = data.getData()[4].subject;
			std::string actualSubject6 = data.getData()[5].subject;
			std::string actualSubject7 = data.getData()[6].subject;
			std::string actualSubject8 = data.getData()[7].subject;
			std::string actualSubject9 = data.getData()[8].subject;

			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(extectedOutputInt, actualOutputInt2);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(extectedOutputInt, actualOutputInt4);
			Assert::AreEqual(extectedOutputInt, actualOutputInt5);
			Assert::AreEqual(extectedOutputInt, actualOutputInt6);
			Assert::AreEqual(extectedOutputInt, actualOutputInt7);
			Assert::AreEqual(extectedOutputInt, actualOutputInt8);
			Assert::AreEqual(extectedOutputInt, actualOutputInt9);

			Assert::AreEqual(extectedOutputInt2, actualOutputInt10);
	
			Assert::AreEqual(expectedSubject1, actualSubject1);
			Assert::AreEqual(expectedSubject2, actualSubject2);
			Assert::AreEqual(expectedSubject3, actualSubject3);
			Assert::AreEqual(expectedSubject1, actualSubject4);
			Assert::AreEqual(expectedSubject2, actualSubject5);
			Assert::AreEqual(expectedSubject3, actualSubject6);
			Assert::AreEqual(expectedSubject1, actualSubject7);
			Assert::AreEqual(expectedSubject2, actualSubject8);
			Assert::AreEqual(expectedSubject3, actualSubject9);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 9;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}

		//Test for sorting by category
		//According to floating, scheduled, deadline tasks
		TEST_METHOD(SortCategoryTest) {
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

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;
			int actualOutputInt4 = 0;
			int actualOutputInt5 = 0;
			int actualOutputInt6 = 0;
			int actualOutputInt7 = 0;
			int actualOutputInt8 = 0;
			int actualOutputInt9 = 0;
			int actualOutputInt10 = 0;
			int actualOutputInt11 = 0;
			int actualOutputInt12 = 0;
			int actualOutputInt13 = 0;
			
			std::string buffer = "buffer";
			std::string input1 = "add b GENERAL";
			std::string input2 = "add a WORK";
			std::string input3 = "add c PERSONAL";
			std::string input4 = "add d ERRAND";

			std::string input5 = "add c ERRAND 5 may";
			std::string input6 = "add a WORK 5/5/2015";
			std::string input7 = "add b GENERAL may 5";
			std::string input8 = "add b PERSONAL may 5";
			
			std::string input9 = "add a PERSONAL 5 pm to 6pm 6aug";
			std::string input10 = "add c ERRAND 6th August 2015 5:00-6:00";
			std::string input11 = "add b GENERAL 6/8/15 from 5 to 6";
			std::string input12 = "add b WORK 6/8/15 from 5 to 6";
			
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			actualOutputInt4 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input5);
			actualOutputInt5 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input6);
			actualOutputInt6 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input7);
			actualOutputInt7 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input8);
			actualOutputInt8 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input9);
			actualOutputInt9 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input10);
			actualOutputInt10 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input11);
			actualOutputInt11 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input12);
			actualOutputInt12 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			parseF.init("sort cat");
			actualOutputInt13 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
			int extectedOutputInt = 0;
			int extectedOutputInt2 = 4;

			std::string expectedCategory1 = "WORK    ";
			std::string expectedCategory2 = "PERSONAL";
			std::string expectedCategory3 = "ERRAND  ";
			std::string expectedCategory4 = "GENERAL ";

			std::string actualCategory1 = data.getData()[0].category;
			std::string actualCategory2 = data.getData()[1].category;
			std::string actualCategory3 = data.getData()[2].category;
			std::string actualCategory4 = data.getData()[3].category;
			std::string actualCategory5 = data.getData()[4].category;
			std::string actualCategory6 = data.getData()[5].category;
			std::string actualCategory7 = data.getData()[6].category;
			std::string actualCategory8 = data.getData()[7].category;
			std::string actualCategory9 = data.getData()[8].category;
			std::string actualCategory10 = data.getData()[9].category;
			std::string actualCategory11 = data.getData()[10].category;
			std::string actualCategory12 = data.getData()[11].category;

			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(extectedOutputInt, actualOutputInt2);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(extectedOutputInt, actualOutputInt4);
			Assert::AreEqual(extectedOutputInt, actualOutputInt5);
			Assert::AreEqual(extectedOutputInt, actualOutputInt6);
			Assert::AreEqual(extectedOutputInt, actualOutputInt7);
			Assert::AreEqual(extectedOutputInt, actualOutputInt8);
			Assert::AreEqual(extectedOutputInt, actualOutputInt9);
			Assert::AreEqual(extectedOutputInt, actualOutputInt10);
			Assert::AreEqual(extectedOutputInt, actualOutputInt11);
			Assert::AreEqual(extectedOutputInt, actualOutputInt12);

			Assert::AreEqual(extectedOutputInt2, actualOutputInt13);
	
			Assert::AreEqual(expectedCategory1, actualCategory1);
			Assert::AreEqual(expectedCategory2, actualCategory2);
			Assert::AreEqual(expectedCategory3, actualCategory3);
			Assert::AreEqual(expectedCategory4, actualCategory4);
			Assert::AreEqual(expectedCategory1, actualCategory5);
			Assert::AreEqual(expectedCategory2, actualCategory6);
			Assert::AreEqual(expectedCategory3, actualCategory7);
			Assert::AreEqual(expectedCategory4, actualCategory8);
			Assert::AreEqual(expectedCategory1, actualCategory9);
			Assert::AreEqual(expectedCategory2, actualCategory10);
			Assert::AreEqual(expectedCategory3, actualCategory11);
			Assert::AreEqual(expectedCategory4, actualCategory12);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 12;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}

		//Test for sorting by priority
		//According to floating, scheduled, deadline tasks
		TEST_METHOD(SortPriorityTest) {
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

			int actualOutputInt = 0;
			int actualOutputInt2 = 0;
			int actualOutputInt3 = 0;
			int actualOutputInt4 = 0;
			int actualOutputInt5 = 0;
			int actualOutputInt6 = 0;
			int actualOutputInt7 = 0;
			int actualOutputInt8 = 0;
			int actualOutputInt9 = 0;
			int actualOutputInt10 = 0;
			
			std::string buffer = "buffer";
			std::string input1 = "add b MED";
			std::string input2 = "add a LOW";
			std::string input3 = "add c HIGH";

			std::string input4 = "add c HIGH 5 may";
			std::string input5 = "add a MED 5/5/2015";
			std::string input6 = "add b LOW may 5";
			
			std::string input7 = "add a LOW 5 pm to 6pm 6aug";
			std::string input8 = "add c HIGH 6th August 2015 5:00-6:00";
			std::string input9 = "add b MED 6/8/15 from 5 to 6";
			
			parseF.init(input1);
			actualOutputInt = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			actualOutputInt2 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			actualOutputInt3 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			actualOutputInt4 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input5);
			actualOutputInt5 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input6);
			actualOutputInt6 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input7);
			actualOutputInt7 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input8);
			actualOutputInt8 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input9);
			actualOutputInt9 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			parseF.init("sort priority");
			actualOutputInt10 = parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
				
			int extectedOutputInt = 0;
			int extectedOutputInt2 = 4;

			std::string expectedPriority1 = "HIGH";
			std::string expectedPriority2 = "MED ";
			std::string expectedPriority3 = "LOW ";

			std::string actualPriority1 = data.getData()[0].priority;
			std::string actualPriority2 = data.getData()[1].priority;
			std::string actualPriority3 = data.getData()[2].priority;
			std::string actualPriority4 = data.getData()[3].priority;
			std::string actualPriority5 = data.getData()[4].priority;
			std::string actualPriority6 = data.getData()[5].priority;
			std::string actualPriority7 = data.getData()[6].priority;
			std::string actualPriority8 = data.getData()[7].priority;
			std::string actualPriority9 = data.getData()[8].priority;

			Assert::AreEqual(extectedOutputInt, actualOutputInt);
			Assert::AreEqual(extectedOutputInt, actualOutputInt2);
			Assert::AreEqual(extectedOutputInt, actualOutputInt3);
			Assert::AreEqual(extectedOutputInt, actualOutputInt4);
			Assert::AreEqual(extectedOutputInt, actualOutputInt5);
			Assert::AreEqual(extectedOutputInt, actualOutputInt6);
			Assert::AreEqual(extectedOutputInt, actualOutputInt7);
			Assert::AreEqual(extectedOutputInt, actualOutputInt8);
			Assert::AreEqual(extectedOutputInt, actualOutputInt9);

			Assert::AreEqual(extectedOutputInt2, actualOutputInt10);
	
			Assert::AreEqual(expectedPriority1, actualPriority1);
			Assert::AreEqual(expectedPriority2, actualPriority2);
			Assert::AreEqual(expectedPriority3, actualPriority3);
			Assert::AreEqual(expectedPriority1, actualPriority4);
			Assert::AreEqual(expectedPriority2, actualPriority5);
			Assert::AreEqual(expectedPriority3, actualPriority6);
			Assert::AreEqual(expectedPriority1, actualPriority7);
			Assert::AreEqual(expectedPriority2, actualPriority8);
			Assert::AreEqual(expectedPriority3, actualPriority9);

			//Test for dataStore functionality
			int ExpectedDataBaseSize = 9;
			int actualDataBaseSize = data.getData().size();
			Assert::AreEqual(ExpectedDataBaseSize, actualDataBaseSize);
		}
		
	};
	
	//@author A0116237l
	TEST_CLASS(ListFulDeleteTest) {
	public:

		//Test delete by a single index
		TEST_METHOD(DeleteSingleTest) {
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
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input5);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			std::string expectednewFirst = "CS project meeting";
			std::string actualnewFirst = data.getData()[0].subject;

			Assert::AreEqual(expectednewFirst, actualnewFirst);
		}

		//Test delete by multiple indexes
		TEST_METHOD(DeleteMultipleTest) {
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
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input5);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			std::string expectednewFirst = "IE2100 homework 7";
			std::string actualnewFirst = data.getData()[0].subject;

			Assert::AreEqual(expectednewFirst, actualnewFirst);
		}

		//Test delete all
		TEST_METHOD(DeleteAllTest) {
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
			std::string input5 = "delete all";
			std::string buffer = "buffer";

			parseF.init(input1);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
			int actualDataSize = data.getData().size();
			int expectedDataSize = 3;
			Assert::AreEqual(expectedDataSize, actualDataSize);
			
			parseF.init(input5);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			int actualDataSize2 = data.getData().size();
			int expectedDataSize2 = 0;
			Assert::AreEqual(expectedDataSize2, actualDataSize2);
		}

	};
	
	//@author A0110670W
	TEST_CLASS(ListFulRemainingTest) {
	public:
		
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

	};
	
	//@author A0115871E
	TEST_CLASS(ListFulClearTest) {
	public:
	
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
			data.getUndoActionLog().push_back(buffer);

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

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
			data.getUndoActionLog().push_back(buffer);

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
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
			data.getUndoActionLog().push_back(buffer);

			parseF.init(input2);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			parseF.init(input3);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

			parseF.init(input4);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);
			
			parseF.init(input5);
			parseF.carryOutCommand(data, errMsg, floating, scheduled, deadline);
			data.getUndoActionLog().push_back(buffer);

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