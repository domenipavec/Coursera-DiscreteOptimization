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
#include <set>
#include <ostream>

struct Edge {
    uint16_t v1;
    uint16_t v2;
};

class SubGraph;

class Graph {
    public:
        Graph(const char * const fn);
        Graph(uint16_t nv);
        std::vector<SubGraph *> * cliques();
        SubGraph * neighbours(uint16_t v);
        
    public:
        uint16_t nVertices;
        uint32_t nEdges;
        Edge * edges;
        std::vector<uint16_t> * edgesTo;
        
    private:
        void BronKerbosch2(SubGraph * R, SubGraph * P, SubGraph * X);
        std::vector<SubGraph *> * storage;
};

class SubGraph: public Graph {
    public:
        SubGraph(Graph * p, std::set<uint16_t> * s);
        ~SubGraph();
        SubGraph * sum(SubGraph * s);
        SubGraph * difference(SubGraph *s);
        SubGraph * intersection(SubGraph *s);
        SubGraph * add(uint16_t v);
        SubGraph * remove(uint16_t v);
        
        Graph * parent;
        std::set<uint16_t> * vertices;
};

std::ostream &operator<<(std::ostream &os, SubGraph const &s);

#endif
