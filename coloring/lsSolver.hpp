/*
 * lsSolver.hpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#ifndef LSSOLVER_HPP
#define LSSOLVER_HPP

#include <stdint.h>
#include <vector>
#include <utility>

#include "graph.hpp"
#include "solution.hpp"
#include "solution.hpp"

typedef std::vector<uint16_t> intList;
typedef std::unordered_set<uint16_t> intSet;

class LSState {
    public:
        LSState(const LSState & s);
        LSState(Graph * g, const Solution & s);
        
        Graph * graph;
        intList verticesColors;
        uint16_t nVertices;
        uint16_t nColors;
        intSet infeasible;
};

class LSSolver {
    public:
        LSSolver(Graph * g, const Solution &s);
        void solve();
        Solution solution();
        
    
        Graph * graph;
        LSState state;
};

#endif
