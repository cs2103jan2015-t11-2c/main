#include "stdafx.h"
#include "CppUnitTest.h"
#include "Add.h"
#include "Add.cpp"
#include "DataStore.cpp"
#include "Edit.h"
#include "Edit.cpp"
#include "Delete.h"
#include "Delete.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLogic
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(AddMethod1)
		{
			DataStore test;
			Add addTest;
	        int index = 1;
			std::string filename = "file.txt";

			addTest.addContent(filename, index, "Meeting with Project Group", 1200 , 1230, 12, 11, 2015, "Low", "Personal", test);

			std::string expectedSubject = "Meeting with Project Group";
			std::string expectedCategory = "Personal";
			std::string expectedPriority = "Low";

			std::string subject = test.getSubject(0);
			std::string category = test.getCategory(0);
			std::string priority = test.getPriority(0);

			Assert::AreEqual(expectedSubject, subject);
			Assert::AreEqual(expectedCategory, category);
			Assert::AreEqual(expectedPriority, priority);
		
		
		}

		TEST_METHOD(EditSubject)
		{
			DataStore test;
			Add add;
			Edit edit;
	        int index = 1;
			std::string filename = "file.txt";

			add.addContent(filename, index, "Dinner date", 1800 , 2000, 31, 03, 2015, "Low", "Personal", test);
			add.addContent(filename, index, "Time to Sleep", 1500 , 1700, 31, 03, 2015, "Low", "Personal", test);

			//edit function takes in the displayed index
			edit.editFunction(filename, test, "subject", "Time to exercise~!", 2);

			std::string expectedSubject = "Time to exercise~!";

			std::string subject = test.getSubject(1);

			Assert::AreEqual(expectedSubject, subject);

		
		}

		TEST_METHOD(DeleteMethod1)
		{
			DataStore test;
			Add addTest;
			Delete deleteTest;
	        int index = 1;
			std::string filename = "file.txt";

			addTest.addContent(filename, index, "Meeting with Project Group", 1200 , 1230, 12, 11, 2015, "Low", "Personal", test);
			addTest.addContent(filename, index, "Clubbing with the gang", 2100 , 2300, 12, 11, 2015, "High", "Work", test);
			deleteTest.deleteContent(filename, test, 1);

			std::string expectedSubject = "Clubbing with the gang";
			std::string expectedCategory = "Work";
			std::string expectedPriority = "High";

			std::string subject = test.getSubject(0);
			std::string category = test.getCategory(0);
			std::string priority = test.getPriority(0);

			Assert::AreEqual(expectedSubject, subject);
			Assert::AreEqual(expectedCategory, category);
			Assert::AreEqual(expectedPriority, priority);
		}

		TEST_METHOD(EditTime)
		{
			DataStore test;
			Add add;
			Edit edit;
	        int index = 1;
			std::string filename = "file.txt";

			add.addContent(filename, index, "Go out with boyfriend", 1800 , 2000, 31, 03, 2015, "Low", "Personal", test);
			add.addContent(filename, index, "Time to Sleep with boyfriend", 2200 , 2300, 31, 03, 2015, "High", "Personal", test);

			//edit function takes in the displayed index
			edit.editFunction(filename, test, "time", "2100-2300", 2);

			int expectedStartTime = 2100;

			int startTime = test.getStartTime(1);

			Assert::AreEqual(expectedStartTime, startTime);
		}

	};
}