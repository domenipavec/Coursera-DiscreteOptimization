/*
 * main.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include <iostream>

#include "graph.hpp"
#include "solution.hpp"

#include "cpSolver.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "coloring.bin requires one command line argument!" << std::endl;
        return 1;
    }

    static const bool USE_CLIQUES = false;
    
    Graph g(argv[1], USE_CLIQUES);
        
    CPSolver solver(&g);
    solver.solve();
    Solution s = solver.solution();
    
    std::cout << s;

    return 0;
}
