/*
 * cpSolver.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "cpSolver.hpp"

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

State::State(const State & s)
        : colors(s.colors),
        verticesColorSS(s.verticesColorSS), 
        graph(s.graph),
        valid(s.valid),
        solution(s.solution)
{
}

State::State(Graph *g) :
        graph(g), 
        colors(0), 
        verticesColorSS(g->nVertices, ColorSearchSpace()), 
        valid(true),
        solution(false)
{
}

void State::setColor(uint16_t i, uint16_t color) {
    verticesColorSS[i].setColor(color);
    for (Vertices::iterator it = graph->neighbours[i].begin(); 
            it != graph->neighbours[i].end(); 
            ++it) {
        verticesColorSS[*it].clearBit(color);
    }
}

ColorSearchSpace::ColorSearchSpace() {
    for (uint8_t i = 0; i < CSS; i++) {
        colors[i] = 0xFFFFFFFFFFFFFFFFULL;
    }
}

bool ColorSearchSpace::isBitSet(uint16_t n) const {
    uint8_t i = n/64;
    uint8_t bit = n%64;
    return (colors[i] & (1ULL << bit)) != 0;
}

void ColorSearchSpace::clearBit(uint16_t n) {
    uint8_t i = n/64;
    uint8_t bit = n%64;
    colors[i] &= ~(1ULL << bit);
}

void ColorSearchSpace::setBit(uint16_t n) {
    uint8_t i = n/64;
    uint8_t bit = n%64;
    colors[i] |= (1ULL << bit);    
}

void ColorSearchSpace::setColor(uint16_t n) {
    uint8_t i = n/64;
    uint8_t bit = n%64;
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
