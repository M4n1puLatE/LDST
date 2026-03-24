#pragma once
#include "Tester.h"
#include "LinkList.h"

namespace Tester
{
	class LinkListTester:public Tester<LinkListTester>
	{
		A_TEST;
		Collection::Linear::LinkList<int> containValue = {1,2,3,4,5,6,7,8,9,10,11};
        Collection::Linear::LinkList<int> emptyList;
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
