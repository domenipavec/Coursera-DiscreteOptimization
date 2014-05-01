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
#define PARALLEL_SOLVE 1
#define OPT3_SOLVE 1

Solution lsSolve(const Data & d, const Solution & s) {
#if OPT3_SOLVE == 1
    return opt3Solve(d,opt2Solve(d,s));
#else
    return opt2Solve(d,s);
#endif
}

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
#if PARALLEL_SOLVE == 1
        Solution * solutions[6];
        #pragma omp parallel for
        for (uint8_t i = 0; i < 6; i++) {
            Solution s(d);
            std::random_shuffle(s.order.begin(), s.order.end());
            solutions[i] = new Solution(lsSolve(d,s));
        }
        double total = solutions[0]->getTotal();
        std::cerr << total;
        solution = solutions[0];
        double maxTotal = total;
        for (uint8_t i = 1; i < 6; i++) {
            total = solutions[i]->getTotal();
            std::cerr << ' ' << total;
            if (total < maxTotal) {
                delete solution;
                solution = solutions[i];
            } else {
                delete solutions[i];
            }
        }
        std::cerr << std::endl;
#else
        Solution s(d);
        std::random_shuffle(s.order.begin(), s.order.end());
        solution = new Solution(lsSolve(d,s));
        std::cerr << solution->getTotal() << ' ';
#endif
    } while (solution->getTotal() > 37600.0);
#else
    solution = new Solution(lsSolve(d,greedySolve(d, Solution(d))));
#endif
    
    std::cout << *solution;
    
    return 0;
}
