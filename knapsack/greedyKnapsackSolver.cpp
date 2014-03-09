/*
 * greedyKnapsackSolver.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "knapsackSolver.hpp"
#include "knapsack.hpp"

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<uint32_t, double> dip;

bool sortFunction(dip a, dip b) {
	return a.second < b.second;
}

// Sort by value/weight and use largest
void KnapsackSolver::solve() {
	dip a;
	vector<dip> doubleIdPair(knapsack->nitems, a);
	
	for (uint32_t i = 0; i < knapsack->nitems; i++) {
		doubleIdPair[i].first = i;
		doubleIdPair[i].second = ((double)knapsack->items[i].value) / ((double)knapsack->items[i].weight);
	}

	std::sort(doubleIdPair.begin(), doubleIdPair.end(), sortFunction);
	
	uint32_t totalWeight = 0;
	for (vector<dip>::iterator it = doubleIdPair.begin(); it != doubleIdPair.end(); it++) {
		totalWeight += knapsack->items[it->first].weight;
		if (totalWeight > knapsack->capacity) {
			break;
		}
		total += knapsack->items[it->first].value;
		taken[it->first] = true;
	}
}
