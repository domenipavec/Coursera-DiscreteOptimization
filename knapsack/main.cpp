/*
 * main.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include <iostream>

#include "knapsack.hpp"
#include "knapsackSolver.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "knapsack requires one command line argument!";
		return 1;
	}
	
	Knapsack k(argv[1]);
	
	KnapsackSolver ks(&k);
	
	ks.solve();
		
	std::cout << ks.solution();
	
	return 0;
}
