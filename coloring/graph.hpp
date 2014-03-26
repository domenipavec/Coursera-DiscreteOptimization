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
#include <unordered_set>
#include <ostream>
#include <utility>

typedef std::pair<uint16_t, uint16_t> Edge;
typedef std::unordered_set<uint16_t> Vertices;

class Graph {
    public:
        Graph(const char * const fn, bool c);
        
    public:
        uint16_t nVertices;
        uint32_t nEdges;
        std::vector<Edge> edges;
        Vertices vertices;
        std::vector<Vertices> neighbours;
        std::vector<Vertices> cliques;
        bool useCliques;
        
    private:
        void BronKerbosch2(const Vertices & R, Vertices P, Vertices X);
};

Vertices sum(const Vertices & vs1, const Vertices & vs2);
Vertices difference(const Vertices & vs1, const Vertices & vs2);
Vertices intersection(const Vertices & vs1, const Vertices & vs2);

std::ostream &operator<<(std::ostream &os, const Vertices &vs);

#endif
