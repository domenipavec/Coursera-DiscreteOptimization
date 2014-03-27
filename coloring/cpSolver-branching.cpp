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
vector_t vertexIndexNumberOfEdges;

State * solveRecursion(const State &s, uint16_t level) {    
    // get real index based on ordering
    uint16_t i = vertexIndexNumberOfEdges[level].first;
    
    // debug output
    if (level < 7) {
        std::cerr << level << ", " << s.colors << ", " << s.verticesColorSS[vertexIndexNumberOfEdges[level - 1].first].firstBit() << std::endl;
    }
    
    // at deepest level return first color
    if (level == s.graph->nVertices - 1) {
        uint16_t color = s.verticesColorSS[i].firstBit();
        if (color < s.maxColors) {
            State *sol = new State(s);
            sol->setColor(i, color);
            sol->solution = true;
            return sol;
        } else {
            return NULL;
        }
    }
    
    // if already set
    if (s.verticesColorSS[i].set) {
        return solveRecursion(s, level+1);
    }
    
    // make a queue of all possible branches
    std::vector<State *> branches;
    State * newState = NULL;
    // all available colors
    for (uint16_t c = 0; c < s.colors; c++) {
        if (s.verticesColorSS[i].isBitSet(c)) {
            newState = new State(s);
            newState->setColor(i, c);
            if (newState->valid) {
                branches.push_back(newState);
            } else {
                delete newState;
            }
        }
    }
    // try using new color
    if (s.colors < s.maxColors) {
        newState = new State(s);
        newState->setColor(i, s.colors);
        if (newState->valid) {
            newState->colors++;
            branches.push_back(newState);
        } else {
            delete newState;
        }
    }
    
    // try all branches for solution
    newState = NULL;
    for (std::vector<State *>::iterator it = branches.begin(); it != branches.end(); ++it) {
        State * sp = (*it);
        if (newState == NULL) {
            State * sr = solveRecursion(*sp, level+1);
            if (sr != NULL && sr->solution) {
                newState = sr;
            }
        }
        delete sp;
    }
    return newState;
}

void CPSolver::solve() {
    // sort by number of edges descending
    for (uint16_t i = 0; i < graph->nVertices; i++) {
        vertexIndexNumberOfEdges.push_back(std::make_pair(i, graph->neighbours[i].size()));
    }
    std::sort(vertexIndexNumberOfEdges.begin(), vertexIndexNumberOfEdges.end(), sortFunction);
    
    // recursive with increasing maxcolors to find optimal solution
    static const uint16_t MAXMAXCOLORS = 120;
    for (uint16_t max = 2; max < MAXMAXCOLORS; max++) {
        std::cerr << "Running for " << max << " colors." << std::endl;
        state.maxColors = max;
        State * s = solveRecursion(state, 0);
        if (s != NULL && s->solution) {
            optimal = true;
            state = *s;
            break;
        }
        delete s;
    }
    
    if (!optimal) {
        std::cerr << "No solution." << std::endl;
    }
    
    optimal = false;
}
