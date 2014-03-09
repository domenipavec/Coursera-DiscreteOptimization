/*
 * knapsackSolver.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "knapsackSolver.hpp"
#include "knapsack.hpp"

#include <sstream>

using namespace std;

KnapsackSolver::KnapsackSolver(Knapsack * ks) 
		: knapsack(ks), optimal(false), total(0) {
	taken = new bool[ks->nitems];
	for (uint32_t i = 0; i < ks->nitems; i++) {
		taken[i] = false;
	}
}

// format solution (check handout.pdf for format)
string KnapsackSolver::solution() {
	stringstream ret("");
	ret << total << ' ' << optimal << endl;
	for (uint32_t i = 0; i < knapsack->nitems; i++) {
		ret << taken[i] << ' ';
	}
	return ret.str();
}
