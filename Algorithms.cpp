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
		else
			if(*it <= *next) ;
			else
			{
				return false;
			}
	}
	return true;
}


template<typename T>
void FillContainer(std::vector<T>& vec)
{
	T val;
	while(std::cin >> val)
		vec.push_back(val);
	std::cin.clear();
}

template<typename Iter>
void PrintContainer(Iter first, Iter last)
{
	cout << "Print Container\n";
	while(first != last)
	{
		cout << *first << " ";
		++first;
	}
}

//void TestForEach()
//{
//	class Functor
//	{
//	public:
//		void operator()(int& i) { i *= 2; }
//	} func;
//
//	std::cout << "Test algorithm for_each\n";
//	std::vector<int> vec;
//	std::cout << "Filling Container:\n";
//	FillContainer(vec);
//	std::for_each(vec.begin(), vec.end(), func);
//
//	PrintContainer(vec.begin(), vec.end(), std::cout);
//}

void TestFind()
{
	//int i;

	//class Functor
	//{
	//public:
	//	bool operator()(int i) { return i > 20; }
	//} func;
	////FIND
	//std::cout << "Test algorithm find\n";
	//std::vector<int> vec;
	//std::cout << "Filling Container:\n";
	//FillContainer(vec);
	//
	//std::cout << "Value to search: ";
	//std::cin >> i;

	//std::vector<int>::iterator iter = std::find(vec.begin(), vec.end(), i);
	//if(iter != vec.end())
	//	std::cout << "Value found: " << *iter << std::endl;
	//else
	//	std::cout << "Value not found !"<< std::endl;

	////FIND_IF
	//std::cout << "Test algorithm find_if\n";
	//iter = find_if(vec.begin(), vec.end(), func);
	//if(iter != vec.end())
	//	std::cout << "First element > 20: " <<  *iter << std::endl;
	//else
	//	std::cout << "Value not found !"<< std::endl;

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


	return 0;
}

