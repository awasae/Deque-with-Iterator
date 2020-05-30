#pragma once
#include <algorithm>
//#include "my_deque_iterator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <sstream>
#include <string>
// declare your my_deque class here

using namespace std;
class my_deque_iterator;

class my_deque {
public:
	my_deque(size_t initial_size);
	my_deque(const my_deque& d);
	~my_deque();
	size_t get_used();
	size_t get_size();
	size_t get_lIndex();
	size_t get_rIndex();
	void push_back(int v);
	void push_front(int v);
	int pop_back();
	int pop_front();
	int* get_mem();
	int& operator[](const size_t& i);
	my_deque_iterator begin();
	my_deque_iterator end();

	int* deque_array;
	size_t size;
	int* rIndex;
	int* lIndex;
	unsigned long long middle_point;
	unsigned long long start;
	unsigned long long End;

};
