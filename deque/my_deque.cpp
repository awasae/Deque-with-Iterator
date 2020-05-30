// define my_deque here
#include "my_deque.h"
#include "my_deque_iterator.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <sstream>
#include <string>

using namespace std;

my_deque::my_deque(size_t initial_size) {
	this->size = initial_size;
	start = 0;
	End = initial_size - 1;
	middle_point = start + (End - start) / 2;
	deque_array = new int[initial_size];
	lIndex = &deque_array[middle_point];
	rIndex = lIndex + 1;
}

my_deque::my_deque(const my_deque& d) {
	start = 0;
	End = d.size - 1;
	middle_point = d.middle_point;
	size = d.size;
	deque_array = new int[size];
	if (deque_array) {
		std::copy(d.deque_array, d.deque_array + size, deque_array);
	}
	lIndex = d.lIndex;
	rIndex = d.rIndex;
}

my_deque::~my_deque() {
	delete[] deque_array;
}

size_t my_deque::get_size() {
	return this->size;
}

size_t my_deque::get_lIndex() {
	return lIndex-&deque_array[0];
}

size_t my_deque::get_rIndex() {
	return rIndex-&deque_array[0];
}

size_t my_deque::get_used() {
	size_t left = this->lIndex - &deque_array[0];
	left++;
	size_t right = this->rIndex - &deque_array[0];
	return right -left;
}

void my_deque::push_back(int v) {
	//create a new array if the element become more than the space available
	this->deque_array[this->get_rIndex()] = v;
	this->rIndex++;
	unsigned long long elements = this->get_used();
	unsigned long long space = this->get_size() / 2;

	// recentring the deque_array
	if (elements <= space && (this->get_rIndex() == this->get_size())) {
		int x = 1;
		this->start = 0;
		this->End = (this->size - 1) - (this->get_used());
		this->middle_point = start + (End - start) / 2;

		int* dbl = new int[this->size];
		for (unsigned long long i = middle_point+1; i <= (middle_point + this->get_used()); i++) {

			dbl[i] = deque_array[this->get_lIndex() + x];
			x++;
		}
		delete[] deque_array;
		this->deque_array = dbl;
		this->lIndex = &deque_array[middle_point];
		this->rIndex = &deque_array[this->get_lIndex()+1]+elements;
	}

	//resizing the deque_array
	if(elements>space && (this->get_rIndex() >= this->get_size())){
		int x = 1;
		this->size *= 2;
		this->start = 0;
		this->End = (this->size -1) - (this->get_used());
		this->middle_point =  start + (End - start) / 2;
		
		int* dbl = new int[this->size];
		
		//cout << "RIndex: " << this->get_rIndex() <<endl;
		for (unsigned long long i = middle_point; i < (middle_point+this->get_used()); i++) {
			dbl[i] = deque_array[this->get_lIndex()+x];
			x++;
		}
		delete[] deque_array;
		this->deque_array = dbl;
		this->lIndex = &deque_array[middle_point - 1];
		this->rIndex = this->lIndex+(x);
	}
}

void my_deque::push_front(int v) {
	this->deque_array[this->get_lIndex()] = v;
	this->lIndex--;
	unsigned long long elements = this->get_used();
	unsigned long long space = this->get_size() / 2;

	//recentring if the number of elements are less than the size and the lIndex is out of bounds
	if (elements <= space && (this->lIndex == &deque_array[0])) {
		int x = 1;
		this->start = 0;
		this->End = (this->size - 1) - (this->get_used());
		this->middle_point = start + (End - start) / 2;

		int* dbl = new int[this->size];
		for (unsigned long long i = middle_point + 1; i <= (middle_point + this->get_used()); i++) {

			dbl[i] = deque_array[this->get_lIndex() + x];
			x++;
		}
		delete[] deque_array;
		this->deque_array = dbl;
		this->lIndex = &deque_array[middle_point];
		this->rIndex = &deque_array[this->get_lIndex() + 1] + elements;
	}

	//resize if the number of elements are gratern than size/2 and lIndex is out of bounds
	if (elements > space && (this->lIndex == &deque_array[0])) {
		int x = 1;
		this->size *= 2;
		this->start = 0;
		this->End = (this->size - 1) - (this->get_used());
		this->middle_point = start + (End - start) / 2;

		int* dbl = new int[this->size];

		//cout << "RIndex: " << this->get_rIndex() << endl;
		for (unsigned long long i = middle_point; i < (middle_point + this->get_used()); i++) {
			dbl[i] = deque_array[this->get_lIndex() + x];
			x++;
		}
		delete[] deque_array;
		this->deque_array = dbl;
		this->lIndex = &deque_array[middle_point - 1];
		this->rIndex = this->lIndex + (x);
	}
}

int my_deque::pop_front() {
	if ((this->get_lIndex() + 1) != (this->get_rIndex())) {
		int popFront{ this->deque_array[this->get_lIndex() + 1] };
		this->lIndex++;
		unsigned long long elements = this->get_used();
		unsigned long long space = this->get_size() / 8;
		if (elements < space && (this->get_lIndex() + 1) != (this->get_rIndex())) {
			int x = 1;
			this->size /= 2;
			this->start = 0;
			this->End = (this->size - 1) - (this->get_used());
			this->middle_point = start + (End - start) / 2;

			int* dbl = new int[this->size];

			//cout << "RIndex: " << this->get_rIndex() << endl;
			for (unsigned long long i = middle_point; i < (middle_point + this->get_used()); i++) {
				dbl[i] = deque_array[this->get_lIndex() + x];
				x++;
			}
			delete[] deque_array;
			this->deque_array = dbl;
			this->lIndex = &deque_array[middle_point - 1];
			this->rIndex = this->lIndex + (x);
		}
		return popFront;
	}
	else {
		throw std::out_of_range("No more element in the Deque");
	}
}

int my_deque::pop_back() {
	if ((this->get_rIndex() - 1) != (this->get_lIndex())) {
		int popBack{ this->deque_array[this->get_rIndex() - 1] };
		this->rIndex--;
		unsigned long long elements = this->get_used();
		unsigned long long space = this->get_size() / 8;
	
		if (elements < space && (this->get_rIndex() - 1) != (this->get_lIndex())) {
			cout << "Elements: " << elements << endl;
			cout << "Space: " << space << endl;
			int x = 1;
			this->size /= 2;
			this->start = 0;
			this->End = (this->size - 1) - (this->get_used());
			this->middle_point = start + (End - start) / 2;

			int* dbl = new int[this->size];
			for (unsigned long long i = middle_point; i < (middle_point + this->get_used()); i++) {
				dbl[i] = deque_array[this->get_lIndex() + x];
				x++;
			}
			//delete[] deque_array;
			this->deque_array = dbl;
			this->lIndex = &deque_array[middle_point - 1];
			this->rIndex = this->lIndex + (x);
		}
		return popBack;
	}
	else { 
		throw std::out_of_range("No more element in the Deque");
	}
}

int& my_deque::operator[](const size_t& i) {
	int* leftValid = this->lIndex + i+1;
	size_t leftIndex = leftValid - &deque_array[0];

	if ((leftIndex >this->get_lIndex()) && (leftIndex <this->get_rIndex())) {
		return *&deque_array[i + (this->get_lIndex() + 1)];
	}
	else {
		throw std::logic_error("Index out of bounds");
	}
}

my_deque_iterator my_deque::begin() {
	my_deque_iterator Iterator(this->lIndex+1,this);
	if (this->get_used() == 0) {
		my_deque_iterator Iterator(this->rIndex-1, this);
	}
	return Iterator;	
}

my_deque_iterator my_deque::end() {
	my_deque_iterator Iterator(this->rIndex, this);
	return Iterator;
}

int* my_deque::get_mem() {
	return deque_array;
}