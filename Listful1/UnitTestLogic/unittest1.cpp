#include "stdafx.h"
#include "CppUnitTest.h"
#include "Add.h"
#include "Add.cpp"
#include "DataStore.cpp"


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

	};
}