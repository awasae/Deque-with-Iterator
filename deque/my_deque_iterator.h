#pragma once
#include "my_deque.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <sstream>
#include <string>

// declare my_deque_iterator here

using namespace std;

class my_deque_iterator {
public:
	my_deque_iterator(int*, my_deque*);
	my_deque_iterator operator+(int n);
	my_deque_iterator& operator+=(int n);
	int& operator*();
	bool operator<(const my_deque_iterator compare_against)const;
	bool operator==(const my_deque_iterator)const;
	int* get_mem();

private:
	my_deque* deque;
	int* curr;
};