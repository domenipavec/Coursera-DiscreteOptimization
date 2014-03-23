/*
 * cpSolver.hpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#ifndef CPSOLVER_HPP
#define CPSOLVER_HPP

#include <stdint.h>

#include "graph.hpp"
#include "solution.hpp"

static const uint8_t CSS = 3; // number of 64 bit integers in color search space

class ColorSearchSpace {
    public:
        ColorSearchSpace();
        bool isBitSet(uint16_t n);
        void clearBit(uint16_t n);       
        void setBit(uint16_t n);
        uint16_t firstBit();
    private:
        uint8_t firstBit64(const uint64_t i);
        uint64_t colors[CSS];
};

class State {
    public:
        State(Graph * g);
        State(State * s);
        State(ColorSearchSpace * css, Graph * g);
        
        ColorSearchSpace * verticesColorSS;
        Graph * graph;
        uint16_t colors;
};

class CPSolver {
    public:
        CPSolver(Graph * g);
        void solve();
        Solution * solution();
        
    
        Graph * graph;
        State * state;
        bool optimal;
};

#endif