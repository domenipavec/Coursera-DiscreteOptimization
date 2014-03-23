/*
 * graph.hpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdint.h>
#include <vector>

struct Edge {
    uint16_t v1;
    uint16_t v2;
};

class Graph {
    public:
        Graph(const char * const fn);
        
    public:
        uint16_t nVertices;
        uint32_t nEdges;
        Edge * edges;
        std::vector<uint16_t> * edgesTo;
};

#endif
