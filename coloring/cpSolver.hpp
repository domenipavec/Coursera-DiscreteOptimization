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
#include <vector>

#include "graph.hpp"
#include "solution.hpp"

static const uint8_t CSS = 3; // number of 64 bit integers in color search space

class ColorSearchSpace {
    public:
        ColorSearchSpace();
        bool isBitSet(uint16_t n) const;
        void clearBit(uint16_t n);       
        void setBit(uint16_t n);
        void setColor(uint16_t n);
        uint16_t firstBit() const;
    private:
        uint8_t firstBit64(const uint64_t i) const;
        uint64_t colors[CSS];
};

typedef std::vector<ColorSearchSpace> Colors;

class State {
    public:
        State(const State & s);
        State(Graph * g);
        void setColor(uint16_t i, uint16_t color);
        
        Colors verticesColorSS;
        Graph * graph;
        uint16_t colors;
        bool valid;
        bool solution;
};

class CPSolver {
    public:
        CPSolver(Graph * g);
        void solve();
        Solution solution();
        
    
        Graph * graph;
        State state;
        bool optimal;
};

#endif
