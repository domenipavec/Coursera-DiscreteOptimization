/*
 * knapsack.hpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include <string>
#include <stdint.h>

struct KnapsackItem {
	uint32_t weight;
	uint32_t value;
};

class Knapsack {
	public:
		Knapsack(const char * const filename);
	public:
		uint32_t capacity;
		uint32_t nitems;
		KnapsackItem * items;
};

#endif
