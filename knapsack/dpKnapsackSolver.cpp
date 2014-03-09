/*
 * dpKnapsackSolver.cpp
 * Implements dynamic programming solution
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "knapsackSolver.hpp"
#include "knapsack.hpp"

#include <algorithm>

using namespace std;

void KnapsackSolver::solve() {
	// store dp data in table [i][j], i is column (item (starts at 0), j is row (capacity (starts at 0)
	uint32_t ** table = new uint32_t*[knapsack->nitems + 1];
	
	// init first column
	table[0] = new uint32_t[knapsack->capacity + 1];
	for (uint32_t j = 0; j <= knapsack->capacity; j++) {
		table[0][j] = 0;
	}
	
	// fill table
	for (uint32_t i = 1; i <= knapsack->nitems; i++) {
		table[i] = new uint32_t[knapsack->capacity + 1];
		for (uint32_t j = 0; j <= knapsack->capacity; j++) {
			if (knapsack->items[i - 1].weight <= j) {
				table[i][j] = max(
					table[i-1][j], 
					knapsack->items[i-1].value + table[i-1][j - knapsack->items[i - 1].weight]);
			} else {
				table[i][j] = table[i-1][j];
			}
		}		
	}
	
	// get result from table
	optimal = true;
	uint32_t i = knapsack->nitems;
	uint32_t j = knapsack->capacity;
	total = table[i][j];
	while (i > 0 && j > 0) {
		if (table[i][j] != table[i-1][j]) {
			taken[i-1] = true;
			j -= knapsack->items[i-1].weight;
		}
		i--;
	}
	
}
