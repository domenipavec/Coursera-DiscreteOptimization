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

#include "graph.hpp"
#include "solution.hpp"

#include "cpSolver.hpp"
#include "lsSolver.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "coloring.bin requires one command line argument!" << std::endl;
        return 1;
    }

    /* initialize random seed: */
    srand (time(NULL));

    static const bool USE_CLIQUES = false;
    
    Graph g(argv[1], USE_CLIQUES);
        
    CPSolver solver(&g);
    solver.solve();
    Solution s = solver.solution();
    
    LSSolver solverLS(&g, s);
    solverLS.solve();
    Solution sLS = solverLS.solution();
    
    std::cout << sLS;

    return 0;
}
