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

void CPSolver::solve() {
    // sort by number of edges descending
    vector_t vertexIndexNumberOfEdges;
    for (uint16_t i = 0; i < graph->nVertices; i++) {
        vertexIndexNumberOfEdges.push_back(std::make_pair(i, graph->neighbours[i].size()));
    }
    std::sort(vertexIndexNumberOfEdges.begin(), vertexIndexNumberOfEdges.end(), sortFunction);
    
    for (vector_t::iterator it = vertexIndexNumberOfEdges.begin(); 
            it != vertexIndexNumberOfEdges.end(); 
            ++it) {
        
        uint16_t i = it->first;
        //std::cerr << i << "," << it->second << std::endl;
        
        uint16_t color = state.verticesColorSS[i].firstBit();
        state.setColor(i, color);
    }
}
