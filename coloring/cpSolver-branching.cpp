/*
 * cpSolver-greedy.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "cpSolver.hpp"

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

bool sortFunction(std::pair<uint16_t, uint16_t> p1, std::pair<uint16_t, uint16_t> p2) {
    return p1.second > p2.second;
}

typedef std::pair<uint16_t, uint16_t> pair_t;
typedef std::vector<pair_t> vector_t;

void solveRecursion(State **s, uint16_t level, vector_t * indices, const uint16_t maxColors) {
    State * min = NULL;
    uint16_t colors_min = 65535;
    uint16_t i = (*indices)[level].first;
    if (level < 7) {
        std::cerr << level << ", " << (*s)->colors << ", " << (*s)->verticesColorSS[(*indices)[level - 1].first].firstBit() <<std::endl;
    }
    
    // at deepest level return first color
    if (level == ((*s)->graph->nVertices - 1)) {
        uint16_t color = (*s)->verticesColorSS[i].firstBit();
        (*s)->setColor(i, color);
        return;
    }
    
    // loop through available colors
    for (uint16_t c = 0; c < (*s)->colors; c++) {
        if ((*s)->verticesColorSS[i].isBitSet(c)) {
            State * newState = new State(*s);
            newState->setColor(i, c);
            solveRecursion(&newState, level+1, indices, maxColors);
            if (newState != NULL) {
                if (newState->colors < colors_min) {
                    min = newState;
                    colors_min = newState->colors;
                    if (colors_min == (*s)->colors) break;
                } else {
                    delete newState;
                }
            }
        }
    }
    
    // try using new color if we don't have optimal and not at MAX colors
    if (colors_min != (*s)->colors && (*s)->colors < maxColors) {
        State * newState = new State(*s);
        newState->setColor(i, (*s)->colors);
        newState->colors++;
        solveRecursion(&newState, level+1, indices, maxColors);
        if (newState != NULL) {
            if (newState->colors < colors_min) {
                min = newState;
                colors_min = newState->colors;
            } else {
                delete newState;
            }
        }
    }
    
    // return optimal
    delete (*s);
    (*s) = min;    
}

void CPSolver::solve() {
    // sort by number of edges descending
    vector_t vertexIndexNumberOfEdges;
    for (uint16_t i = 0; i < graph->nVertices; i++) {
        vertexIndexNumberOfEdges.push_back(std::make_pair(i, graph->edgesTo[i].size()));
    }
    std::sort(vertexIndexNumberOfEdges.begin(), vertexIndexNumberOfEdges.end(), sortFunction);
    
    // recursive with increasing maxcolors to find optimal solution
    static const uint16_t MAXMAXCOLORS = 20;
    for (uint16_t max = 2; max < MAXMAXCOLORS; max++) {
        std::cerr << "Running for " << max << " colors." << std::endl;
        State * s = new State(state);
        solveRecursion(&s, 0, &vertexIndexNumberOfEdges, max);
        if (s != NULL) {
            optimal = true;
            delete state;
            state = s;
            break;
        }
    }
    
    if (!optimal) {
        std::cerr << "No solution." << std::endl;
    }
    
}
