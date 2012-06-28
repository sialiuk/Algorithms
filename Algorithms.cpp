// Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

void Check(bool condition, size_t line)
{
	if(!condition)
	{
		std::cout << "Check failed in line " << line << std::endl;
	}
}

#define TEST_CHECK(condition) Check(condition, __LINE__);


template<typename FwdIter>
bool CheckSort(FwdIter first, FwdIter last)
{
	while(first != last)
	{
		FwdIter it = first;
		FwdIter next = ++first;
		if(next == last)
		{
			break;
		}
		else if(*it > *next) 
		{
			return false;
		}
	}
	return true;
}

int Generate()
{
	return (rand() % 10 + 1);
}

void TestFind()
{
	vector<int> v;
	auto it = find(v.cbegin(), v.cend(), 0);
	TEST_CHECK(it == v.cend());
	v.push_back(1);
	v.push_back(3);
	v.push_back(6);
	it = find(v.begin(), v.end(), 3);
	TEST_CHECK(it != v.cend() && *it == 3);
	it = find(v.begin(), v.end(), 0);
	TEST_CHECK(it == v.cend());
}

void TestFindIf()
{
	class Functor
	{
	public:
		bool operator()(int i) { return i > 10; }
	} func;

	vector<int> v;
	auto it = find_if(v.cbegin(), v.cend(), func);
	TEST_CHECK(it == v.cend());
	
	v.push_back(1);
	v.push_back(3);
	it = find_if(v.cbegin(), v.cend(), func);
	TEST_CHECK(it == v.cend());
	
	v.push_back(60);
	it = find_if(v.cbegin(), v.cend(), func);
	TEST_CHECK(it != v.cend() && *it > 10);
}

void TestForEach()
{
	class Functor
	{
	public:
		void operator()(int& i) { i *= 2; }
	} func;

	vector<int> v;
	v.push_back(1);
	v.push_back(3);
	for_each(v.begin(), v.end(), func);
	TEST_CHECK(v[0] == 2 && v[1] == 6);
}

void TestEqual()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(3);
	v.push_back(4);
	v.push_back(3);
	v.push_back(1);
	TEST_CHECK(equal(v.begin(), v.end(), v.rbegin()));
	v.push_back(10);
	TEST_CHECK(!equal(v.begin(), v.end(), v.rbegin()));
}

void TestFill()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(3);
	v.push_back(4);
	fill(v.begin(), v.end(), 10);
	for(auto it = v.cbegin(); it != v.cend(); ++it)
	{
		TEST_CHECK(*it == 10);
	}
}

void TestCount()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(1);
	int number = static_cast<int>(count(v.cbegin(), v.cend(), 2));
	TEST_CHECK(number == 0);

	v.push_back(4);
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	number = static_cast<int>(count(v.cbegin(), v.cend(), 2));
	TEST_CHECK(number == 2);

	number = static_cast<int>(count(v.cbegin(), v.cend(), 4));
	TEST_CHECK(number == 1);
}

void TestCopy()
{
	vector<int> v, c;
	v.push_back(4);
	v.push_back(3);
	v.push_back(1);
	v.push_back(2);
	copy(v.cbegin(), v.cend(), back_inserter(c));
	TEST_CHECK(equal(v.cbegin(), v.cend(), c.cbegin()));
}


void TestSort()
{
	class Functor
	{
	public:
		bool operator()(int i, int j) { return i > j; }
	} func;

	vector<int> v;
	v.push_back(4);
	v.push_back(3);
	v.push_back(9);
	v.push_back(7);
	TEST_CHECK(!CheckSort(v.cbegin(), v.cend()));
	sort(v.begin(), v.end());
	TEST_CHECK(CheckSort(v.cbegin(), v.cend()));
	sort(v.begin(), v.end(), func);
	TEST_CHECK(CheckSort(v.rbegin(), v.rend()));
}

void TestBinarySearch()
{
	vector<int> v;
	v.push_back(4);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	sort(v.begin(), v.end());

	TEST_CHECK(!binary_search(v.cbegin(), v.cend(), 10));
	v.push_back(10);
	v.push_back(2);
	sort(v.begin(), v.end());
	TEST_CHECK(binary_search(v.cbegin(), v.cend(), 10));

}

void TestGenerate()
{
	vector<int> v(10);
	generate(v.begin(), v.end(), Generate);
	for(auto it = v.cbegin(); it != v.cend(); ++it)
	{
		TEST_CHECK(*it != 0);
	}
}

void TestRemove()
{
	vector<int> v;
	v.push_back(4);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v.erase(remove(v.begin(), v.end(), 5), v.end());
	
	for(auto it = v.cbegin(); it != v.cend(); ++it)
	{
		TEST_CHECK(*it != 5);
	}
}

void TestRemoveIf()
{
	class Functor
	{
	public:
		bool operator()(int i) { return i < 5; }
	} func;

	vector<int> v;
	v.push_back(4);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v.erase(remove_if(v.begin(), v.end(), func), v.end());
	for(auto it = v.cbegin(); it != v.cend(); ++it)
	{
		TEST_CHECK(*it >= 5);
	}
}

void TestRemoveCopy()
{
	vector<int> v, c;
	v.push_back(4);
	v.push_back(5);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v.push_back(5);
	remove_copy(v.begin(), v.end(), back_inserter(c), 5);

	for(auto it = c.cbegin(); it != c.cend(); ++it)
	{
		TEST_CHECK(*it != 5);
	}
}

void TestRaplace()
{
	vector<int> v;
	v.push_back(4);
	v.push_back(5);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v.push_back(5);

	replace(v.begin(), v.end(), 5, 10);
	
	for(auto it = v.cbegin(); it != v.cend(); ++it)
	{
		TEST_CHECK(*it != 5);
	}
}

void TestReplaceCopy()
{
	vector<int> v, c;
	v.push_back(4);
	v.push_back(5);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v.push_back(5);

	replace_copy(v.begin(), v.end(), back_inserter(c), 5, 10);
	
	for(auto it =c.cbegin(); it != c.cend(); ++it)
	{
		TEST_CHECK(*it != 5);
	}
}

void TestRandomShuffle()
{
	vector<int> v;
	v.push_back(4);
	v.push_back(5);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v.push_back(5);
	sort(v.begin(), v.end());
	TEST_CHECK(CheckSort(v.cbegin(), v.cend()));
	random_shuffle(v.begin(), v.end());
	TEST_CHECK(!CheckSort(v.cbegin(), v.cend()));
}

void TestReverse()
{
	vector<int> v;
	v.push_back(4);
	v.push_back(5);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v.push_back(5);
	sort(v.begin(), v.end());
	TEST_CHECK(CheckSort(v.cbegin(), v.cend()));
	reverse(v.begin(), v.end());
	TEST_CHECK(CheckSort(v.rbegin(), v.rend()));
}

void TestPartition()
{
	vector<int> v;
	v.push_back(4);
	v.push_back(9);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	auto it = 
	partition
	(
		v.begin(), v.end(), 
		[](int i)->bool
		{
			return i < 5;
		}
	);
	v.erase(it, v.end());
	
	for(auto it = v.cbegin(); it != v.cend(); ++it)
	{
		TEST_CHECK(*it < 5);
	}
}

void TestStablePartition()
{
	class Functor
	{
	public:
		bool operator()(int i) { return i > 5; }
	} func;

	vector<int> v;
	v.push_back(4);
	v.push_back(9);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v.push_back(6);
	v.push_back(8);
	sort(v.begin(), v.end());
	auto it = stable_partition(v.begin(), v.end(), func);
	v.erase(it, v.end());
	
	TEST_CHECK(CheckSort(v.cbegin(), v.cend()));

	for(auto it = v.cbegin(); it != v.cend(); ++it)
	{
		TEST_CHECK(*it > 5);
	}
}

void TestUnique()
{
	vector<int> v;
	v.push_back(4);
	v.push_back(4);
	v.push_back(4);
	v.push_back(9);
	v.push_back(9);
	v.push_back(9);
	v.push_back(5);
	v.push_back(4);
	TEST_CHECK(v.size() == 8);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	TEST_CHECK(v.size() == 3);
}

void TestNthElement()
{
	vector<int> v;
	v.push_back(4);
	v.push_back(3);
	v.push_back(10);
	v.push_back(8);
	v.push_back(3);
	v.push_back(3);
	v.push_back(5);
	v.push_back(2);
	auto it = v.begin() + 6;
	
	nth_element(v.begin(), it, v.end());
	TEST_CHECK(*it == 8);
	v.erase(v.begin(), it);
	
	it = find_if(v.begin(), v.end(), [](int i)->bool{ return i < 8; });
	TEST_CHECK(it == v.end());
}

void TestTransform()
{
	vector<int> v, c;
	v.push_back(4);
	v.push_back(3);
	v.push_back(10);
	v.push_back(8);

	transform(v.begin(), v.end(), back_inserter(c), [](int i)->int { return i * 2; });
	TEST_CHECK(v.size() == c.size());
	auto it = find_if(c.begin(), c.end(), [](int i)->bool{ return i < 6; });
	TEST_CHECK(it == c.end());
}

void TestSetDifference()
{
	vector<int> v, c, r;
	v.push_back(5);
	v.push_back(6);
	v.push_back(3);
	v.push_back(10);
	v.push_back(8);

	c.push_back(7);
	c.push_back(3);
	c.push_back(10);
	c.push_back(5);
	c.push_back(6);

	sort(v.begin(), v.end());
	sort(c.begin(), c.end());
	set_difference(v.begin(), v.end(), c.begin(), c.end(), back_inserter(r));

	TEST_CHECK(r[0] == 8);
}

void TestSetUnion()
{
	vector<int> v, c, r;
	v.push_back(3);
	v.push_back(4);
	v.push_back(7);
	
	c.push_back(7);
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	c.push_back(4);

	sort(v.begin(), v.end());
	sort(c.begin(), c.end());

	set_union(v.begin(), v.end(), c.begin(), c.end(), back_inserter(r));
	TEST_CHECK(CheckSort(r.begin(), r.end()));
	unique(r.begin(), r.end());
	TEST_CHECK(r.size() == c.size());
}

void TestSetIntersection()
{
	vector<int> v, c, r;
	v.push_back(3);
	v.push_back(4);
	v.push_back(7);
	
	c.push_back(7);
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	c.push_back(4);

	sort(v.begin(), v.end());
	sort(c.begin(), c.end());

	set_intersection(v.begin(), v.end(), c.begin(), c.end(), back_inserter(r));
	TEST_CHECK(CheckSort(r.begin(), r.end()));
	TEST_CHECK(r.size() == v.size());
}

int _tmain(int argc, _TCHAR* argv[])
{	
	TestFind();
	TestFindIf();
	TestForEach();
	TestEqual();
	TestFill();
	TestCount();
	TestCopy();
	TestSort();
	TestBinarySearch();
	TestGenerate();
	TestRemove();
	TestRemoveIf();
	TestRemoveCopy();
	TestRaplace();
	TestReplaceCopy();
	TestRandomShuffle();
	TestReverse();
	TestPartition();
	TestStablePartition();
	TestUnique();
	TestNthElement();
	TestTransform();
	TestSetDifference();
	TestSetUnion();
	TestSetIntersection();

	return 0;
}

