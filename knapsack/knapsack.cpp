/*
 * knapsack.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "knapsack.hpp"

#include <fstream>

using namespace std;

// load from file (check handout.pdf for format)
Knapsack::Knapsack(const char * const filename) {
	ifstream ifile;
	ifile.open(filename, ios::in);
	if (ifile.is_open()) {
		ifile >> nitems;
		ifile >> capacity;
		items = new KnapsackItem[nitems];
		for (uint32_t i = 0; i < nitems; i++) {
			ifile >> items[i].value;
			ifile >> items[i].weight;
		}
	} else {
		capacity = 0;
		items = NULL;
	}
}
