/*
 * main.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "data.hpp"
#include "solution.hpp"
#include "solver.hpp"

#define RANDOM_SOLVE 1

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "tsp.bin requires one command line argument!" << std::endl;
        return 1;
    }

    /* initialize random seed: */
    srand (time(NULL));

    Data d(argv[1]);

    Solution * solution;
    
#if RANDOM_SOLVE == 1
    do {
        Solution s(d);
        std::random_shuffle(s.order.begin(), s.order.end());
        solution = new Solution(lsSolve(d,s));
        std::cerr << solution->getTotal() << ' ';
    } while (solution->getTotal() > 37600.0);
#else
    solution = new Solution(lsSolve(d,greedySolve(d, Solution(d))));
#endif
    
    std::cout << *solution;
    
    return 0;
}
