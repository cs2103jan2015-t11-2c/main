#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListfulTest {		
	TEST_CLASS(AddTest) {
	public:
		TEST_METHOD(CheckAdd) {
			std::string fileName = "Reminders";
			DataStore data;
			Classes listClass;
			std::string subject = "friend de birthday party at Bishan";
			std::string cat = "PERSONAL";
			std::string priority = "HIGH";
			int day = 1;
			int month = 4;
			int year = 2015;
			int sTime = 1500;
			int eTime = 1900;

			data.get_tempEntry().subject = subject;
			data.get_tempEntry().startTime = sTime;
			data.get_tempEntry().endTime = eTime;
			data.get_tempEntry().day = day;
			data.get_tempEntry().month = month;
			data.get_tempEntry().year = year;
			data.get_tempEntry().category = cat;
			data.get_tempEntry().priority = priority;
			listClass.add.addContent(data, fileName);

			data.get_tempEntry().subject = "CS2103 Version 0.2 Developer Guide";
			data.get_tempEntry().startTime = 1100;
			data.get_tempEntry().endTime = 1200;
			data.get_tempEntry().day = 26;
			data.get_tempEntry().month = 3;
			data.get_tempEntry().year = 2015;
			data.get_tempEntry().category = "WORK";
			data.get_tempEntry().priority = "HIGH";
			listClass.add.addContent(data, fileName);

			Assert::AreEqual(data.getData()[1].subject, data.get_tempEntry().subject);
			Assert::AreEqual(data.getData()[1].category, data.get_tempEntry().category);
			Assert::AreEqual(data.getData()[1].priority, data.get_tempEntry().priority);
			Assert::AreEqual(data.getData()[1].startTime, data.get_tempEntry().startTime);
			Assert::AreEqual(data.getData()[1].year, data.get_tempEntry().year);
			Assert::AreEqual(data.getData()[1].month, data.get_tempEntry().month);
			Assert::AreEqual(data.getData()[1].day, data.get_tempEntry().day);
			Assert::AreEqual(data.getData()[1].endTime, data.get_tempEntry().endTime);

			Assert::AreEqual(data.getData()[0].subject, subject);
			Assert::AreEqual(data.getData()[0].category, cat);
			Assert::AreEqual(data.getData()[0].priority, priority);
			Assert::AreEqual(data.getData()[0].startTime, sTime);
			Assert::AreEqual(data.getData()[0].year, year);
			Assert::AreEqual(data.getData()[0].month, month);
			Assert::AreEqual(data.getData()[0].day, day);
			Assert::AreEqual(data.getData()[0].endTime, eTime);
		}
	};
}