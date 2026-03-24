#pragma once
#include "Tester.h"
#include "LinkList.h"

namespace Tester
{
	class LinkListTester:public Tester<LinkListTester>
	{
		A_TEST;
		void init();
		bool constructTest();
		bool addTest();
        bool removeTest();
		bool insertTest();
        bool findTest();
		bool rangeTest();
		bool overwriteTest();
		bool getTest();
		bool containsTest();
		bool removeFromTest();
		bool reserveTest();
		bool firstTest();
        bool lastTest();
		bool sizeTest();
		bool emptyTest();
        bool clearTest();
        bool setTest();
		bool countTest();
	};
}
