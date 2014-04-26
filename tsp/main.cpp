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

#include "data.hpp"
#include "solution.hpp"
#include "solver.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "tsp.bin requires one command line argument!" << std::endl;
        return 1;
    }

    /* initialize random seed: */
    srand (time(NULL));

    Data d(argv[1]);

    Solution s = solve(d, Solution(d));
    
    std::cout << s;
    
    s.visualize();
    
    return 0;
}
