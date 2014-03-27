/*
 * cpSolver.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "cpSolver.hpp"

#include <iostream>

CPSolver::CPSolver(Graph * g)
        : graph(g), state(g), optimal(false) {
}

Solution CPSolver::solution() {
    Solution s(graph->nVertices);
    s.optimal = optimal;
    for (Colors::iterator it = state.verticesColorSS.begin(); it != state.verticesColorSS.end(); ++it) {
        s.verticesColors.push_back(it->firstBit());
    } 
    return s;
}

State::State(const State & s) :
        verticesColorSS(s.verticesColorSS), 
        graph(s.graph),
        colors(s.colors),
        maxColors(s.maxColors),
        valid(s.valid),
        solution(s.solution)
{
}

State::State(Graph *g) :
        verticesColorSS(g->nVertices, ColorSearchSpace()), 
        graph(g), 
        colors(0), 
        maxColors(0),
        valid(true),
        solution(false)
{
}

void State::setColor(uint16_t i, uint16_t color) {
    if (!verticesColorSS[i].set) {
        verticesColorSS[i].setColor(color);
        verticesColorSS[i].set = true;
        for (std::vector<uint16_t>::iterator it = graph->neighbours[i].begin(); 
                it != graph->neighbours[i].end(); 
                ++it) {
            clearBit(*it, color);
            if (!valid)
                break;
        }
        if (valid) {
            for (std::vector<uint16_t>::iterator it = graph->neighbours[i].begin(); 
                it != graph->neighbours[i].end(); 
                ++it) {
                // set all unset neighbours that only have one option left
                uint16_t j = *it;
                if (!verticesColorSS[j].set) {
                    uint16_t fb = verticesColorSS[j].firstBit();
                    verticesColorSS[j].clearBit(fb);
                    if (verticesColorSS[j].firstBit() >= maxColors) {
                        setColor(j, fb);
                    } else {
                        verticesColorSS[j].setBit(fb);
                    }
                }
                if (!valid)
                    break;
            }
        }
    }
}

void State::clearBit(uint16_t i, uint16_t bit) {
    if (!verticesColorSS[i].set) {
        verticesColorSS[i].clearBit(bit);
        // check if we still have valid options
        if (verticesColorSS[i].firstBit() >= maxColors) {
            valid = false;
        }
    }
}

ColorSearchSpace::ColorSearchSpace() {
    for (uint8_t i = 0; i < CSS; i++) {
        colors[i] = 0xFFFFFFFFFFFFFFFFULL;
    }
    set = false;
}

bool ColorSearchSpace::isBitSet(uint16_t n) const {
    uint8_t i = n>>6;
    uint8_t bit = n&0x3f;
    return (colors[i] & (1ULL << bit)) != 0;
}

void ColorSearchSpace::clearBit(uint16_t n) {
    uint8_t i = n>>6;
    uint8_t bit = n&0x3f;
    colors[i] &= ~(1ULL << bit);
}

void ColorSearchSpace::setBit(uint16_t n) {
    uint8_t i = n>>6;
    uint8_t bit = n&0x3f;
    colors[i] |= (1ULL << bit);    
}

void ColorSearchSpace::setColor(uint16_t n) {
    uint8_t i = n>>6;
    uint8_t bit = n&0x3f;
    for (uint8_t j = 0; j < CSS; j++) {
        colors[j] = 0;
    }
    colors[i] = (1ULL << bit);
}

uint16_t ColorSearchSpace::firstBit() const {
    uint16_t i = 0;
    while (colors[i] == 0) i++;
    return i*64 + firstBit64(colors[i]);
}

uint8_t ColorSearchSpace::firstBit64(const uint64_t i) const {
    static const int index64[64] = {
        63,  0, 58,  1, 59, 47, 53,  2,
        60, 39, 48, 27, 54, 33, 42,  3,
        61, 51, 37, 40, 49, 18, 28, 20,
        55, 30, 34, 11, 43, 14, 22,  4,
        62, 57, 46, 52, 38, 26, 32, 41,
        50, 36, 17, 19, 29, 10, 13, 21,
        56, 45, 25, 31, 35, 16,  9, 12,
        44, 24, 15,  8, 23,  7,  6,  5  };

    static const uint64_t debruijn64 = 0x07EDD5E59A4E28C2ULL;

    return index64[((i & -i) * debruijn64) >> 58];
}
