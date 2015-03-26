#include "stdafx.h"
#include "CppUnitTest.h"
#include "Add.h"
#include "Add.cpp"
#include "DataStore.cpp"
#include "Edit.h"
#include "Edit.cpp"


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
	};
}