/*
 * graph.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "graph.hpp"

#include <fstream>
#include <iostream>

using namespace std;

Graph::Graph(const char * const fn, bool c)
        : useCliques(c) {
    ifstream ifile;
    ifile.open(fn, ios::in);
    if (ifile.is_open()) {
        ifile >> nVertices;
        ifile >> nEdges;
        cerr << "Vertices: " << nVertices << ", Edges: " << nEdges << endl;
        for (uint16_t i = 0; i < nVertices; i++) {
            vertices.insert(i);
        }
        neighbours.assign(nVertices, Vertices());
        for (uint32_t i = 0; i < nEdges; i++) {
            Edge e;
            ifile >> e.first;
            ifile >> e.second;
            edges.push_back(e);
            neighbours[e.first].insert(e.second);
            neighbours[e.second].insert(e.first);
        }
    } else {
        cerr << "Could not open file " << fn << endl;
    }
    if (useCliques) {
        cerr << "Calculating cliques ..." << endl;
        BronKerbosch2(Vertices(), vertices, Vertices());
        cerr << "Found " << cliques.size() << " cliques." << endl;
    }
}

Vertices sum(const Vertices & vs1, const Vertices & vs2) {
    Vertices vs(vs1);
    vs.insert(vs2.begin(), vs2.end());
    return vs;
}

Vertices difference(const Vertices & vs1, const Vertices & vs2) {
    Vertices vs(vs1);
    for (Vertices::const_iterator it = vs2.cbegin(); it != vs2.cend(); ++it) {
        vs.erase(*it);
    }
    return vs;
}

Vertices intersection(const Vertices & vs1, const Vertices & vs2) {
    Vertices vs;
    for (Vertices::const_iterator it = vs1.cbegin(); it != vs1.cend(); ++it) {
        if (vs2.find(*it) != vs2.cend()) {
            vs.insert(*it);
        }
    }
    return vs;
}

std::ostream &operator<<(std::ostream &os, const Vertices &vs) {
    for (Vertices::const_iterator it = vs.cbegin(); it != vs.cend(); ++it) {
        std::cerr << *it << " ";
    }
    return os;
}

void Graph::BronKerbosch2(const Vertices & R, Vertices P, Vertices X) {
    if (P.empty() && X.empty()) {
        cliques.push_back(R);
        return;
    }
    
    uint16_t pivot = *(sum(P, X).begin());
    
    // P difference (neighbours of pivot)
    const Vertices pdnp = difference(P, neighbours[pivot]);

    for (Vertices::const_iterator it = pdnp.cbegin(); it != pdnp.cend(); ++it) {
        Vertices Radd(R);
        Radd.insert(*it);
        
        BronKerbosch2(Radd, intersection(P, neighbours[*it]), intersection(X, neighbours[*it]));
        
        P.erase(*it);
        X.insert(*it);
    }
}
