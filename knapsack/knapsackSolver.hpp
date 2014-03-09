/*
 * knapsackSolver.hpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#ifndef KNAPSACK_SOLVER_HPP
#define KNAPSACK_SOLVER_HPP

#include <string>
#include <stdint.h>

class Knapsack;

class KnapsackSolver {
	public:
		KnapsackSolver(Knapsack * ks);
		void solve();
		std::string solution();
	private:
		Knapsack * knapsack;
		bool optimal;
		uint32_t total;
		bool * taken;
};


#endif
