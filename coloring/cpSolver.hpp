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

static const uint8_t CSS = 2; // number of 64 bit integers in color search space

class ColorSearchSpace {
    public:
        ColorSearchSpace(uint16_t max);
        bool isBitSet(const uint16_t n) const;
        bool isPowerOfTwo() const;
        void clearBit(const uint16_t n);       
        void setBit(const uint16_t n);
        void setColor(const uint16_t n);
        uint16_t firstBit() const;
        bool set;

        uint8_t firstBit64(const uint64_t i) const;
        uint64_t colors[CSS];
};

typedef std::vector<ColorSearchSpace> Colors;

class State {
    public:
        State(const State & s);
        State(Graph * g, uint16_t max = 64*CSS);
        void setColor(const uint16_t i, const uint16_t color);
        void clearBit(const uint16_t i, const uint16_t bit);
        
        Colors verticesColorSS;
        Graph * graph;
        uint16_t colors;
        uint16_t maxColors;
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
