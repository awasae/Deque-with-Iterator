// define my_deque_iterator here
#include "my_deque_iterator.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <sstream>
#include <string>


using namespace std;
my_deque_iterator::my_deque_iterator(int* a, my_deque* b) {
	this->deque = b;
	size_t valid = a - &b->deque_array[0];
	if ((valid >= b->get_lIndex()) && (valid <= b->get_rIndex())) {
		this->curr=a;
	}
	else {
		this->curr = nullptr;
	}
}

my_deque_iterator my_deque_iterator::operator+(int n){
	if (n >= 0) {
		my_deque_iterator i(*this);
		i.curr += n;
		return i;
	}
	else {
		this->curr = nullptr;
		return *this;
	}
}

my_deque_iterator& my_deque_iterator::operator+=(int n) {
	if (n >= 0) {
		this->curr += n;
		return *this;
	}
	else {
		this->curr = nullptr;
		return *this;
	}
}

int& my_deque_iterator::operator*() {
	int* a = this->curr;
	size_t valid = a - &this->deque->deque_array[0];
	if ((valid >= this->deque->get_lIndex()) && (valid <= this->deque->get_rIndex())) {
		my_deque d = *this->deque;
		int& x = d[*this->curr];
		return x;
	}
	if(this->curr == nullptr ) {
		throw std::logic_error("Not a valid iterator");
	}
	else {
		throw std::logic_error("Not a valid iterator");
	}
}

bool my_deque_iterator::operator<(const my_deque_iterator compare_against)const {
	if (this->curr < compare_against.curr && this->deque == compare_against.deque) {
		return true;
	}
	if (this->deque != compare_against.deque || this->curr == nullptr || this->deque==nullptr) {
		throw std::logic_error("Not a valid iterator");
	}
	else {
		return false;
	}
}

bool my_deque_iterator::operator==(const my_deque_iterator a)const {
	if (this->curr == a.curr && this->deque == a.deque) {
		return true;
	}
	else {
		return false;
	}
}

int* my_deque_iterator::get_mem() {
	return curr;
}