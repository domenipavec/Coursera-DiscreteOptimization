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

std::ostream &operator<<(std::ostream &os, SubGraph const &s) {
    for (std::set<uint16_t>::iterator it = s.vertices->begin(); it != s.vertices->end(); ++it) {
        std::cerr << *it << " ";
    }
    return os;
}

Graph::Graph(const char * const fn) {
    ifstream ifile;
    ifile.open(fn, ios::in);
    if (ifile.is_open()) {
        ifile >> nVertices;
        ifile >> nEdges;
        cerr << "Vertices: " << nVertices << ", Edges: " << nEdges << endl;
        edges = new Edge[nEdges];
        edgesTo = new vector<uint16_t>[nVertices];
        for (uint32_t i = 0; i < nEdges; i++) {
            ifile >> edges[i].v1;
            ifile >> edges[i].v2;
            edgesTo[edges[i].v1].push_back(edges[i].v2);
            edgesTo[edges[i].v2].push_back(edges[i].v1);
        }
    } else {
        cerr << "Could not open file " << fn << endl;
    }
}

Graph::Graph(uint16_t nv)
        : nVertices(nv), nEdges(0), edges(NULL), edgesTo(new vector<uint16_t>[nVertices]) {
}

// subgraph only implements nvertices and edgesto
SubGraph::SubGraph(Graph * p, std::set<uint16_t> * s)
        : parent(p), vertices(s), Graph(s->size()) {
    uint16_t i = 0;
    for (std::set<uint16_t>::iterator it = vertices->begin(); it != vertices->end(); ++it) {
        edgesTo[i].assign(parent->edgesTo[*it].begin(), parent->edgesTo[*it].end());
        i++;
    }
}

SubGraph::~SubGraph() {
    delete vertices;
}

SubGraph * SubGraph::sum(SubGraph * s) {
    std::set<uint16_t> * newSet = new std::set<uint16_t>(*vertices);
    newSet->insert(s->vertices->begin(), s->vertices->end());
    return new SubGraph(parent, newSet);
}

SubGraph * SubGraph::difference(SubGraph *s) {
    std::set<uint16_t> * newSet = new std::set<uint16_t>(*vertices);
    for (std::set<uint16_t>::iterator it = s->vertices->begin(); it != s->vertices->end(); ++it) {
        newSet->erase(*it);
    }
    return new SubGraph(parent, newSet);
}

SubGraph * SubGraph::intersection(SubGraph *s) {
    std::set<uint16_t> * newSet = new std::set<uint16_t>();
    for (std::set<uint16_t>::iterator it = s->vertices->begin(); it != s->vertices->end(); ++it) {
        if (vertices->find(*it) != vertices->end()) {
            newSet->insert(*it);
        }
    }
    return new SubGraph(parent, newSet);
}

SubGraph * SubGraph::add(uint16_t v) {
    std::set<uint16_t> * newSet = new std::set<uint16_t>(*vertices);
    newSet->insert(v);
    return new SubGraph(parent, newSet);
}

SubGraph * SubGraph::remove(uint16_t v) {
    std::set<uint16_t> * newSet = new std::set<uint16_t>(*vertices);
    newSet->erase(v);
    return new SubGraph(parent, newSet);
    
}

std::vector<SubGraph *> * Graph::cliques() {
    storage = new std::vector<SubGraph *>();
    
    // init full set
    std::set<uint16_t> * full = new std::set<uint16_t>();
    for (uint16_t i = 0; i < nVertices; i++) {
        full->insert(i);
    }
    
    // run algorithm
    BronKerbosch2(new SubGraph(this, new std::set<uint16_t>()), new SubGraph(this, full), new SubGraph(this, new std::set<uint16_t>()));
    
    return storage;
}

SubGraph * Graph::neighbours(uint16_t v) {
    std::set<uint16_t> * neighboursSet = new std::set<uint16_t>();
    for (std::vector<uint16_t>::iterator it = edgesTo[v].begin(); it != edgesTo[v].end(); ++it) {
        neighboursSet->insert(*it);
    }
    return new SubGraph(this, neighboursSet);
}

void Graph::BronKerbosch2(SubGraph * R, SubGraph * P, SubGraph * X) {
    if (P->nVertices == 0 && X->nVertices == 0) {
        storage->push_back(R);
        delete P;
        delete X;
        return;
    }
    
    SubGraph * sumPX = P->sum(X);
    uint16_t pivot = *(sumPX->vertices->begin());
    delete sumPX;
    
    SubGraph * pivotNeighbours = neighbours(pivot);
    SubGraph * pdnu = P->difference(pivotNeighbours);
    delete pivotNeighbours;
    

    for (std::set<uint16_t>::iterator it = pdnu->vertices->begin(); it != pdnu->vertices->end(); ++it) {
        SubGraph * vNeighbours = neighbours(*it);
        BronKerbosch2(R->add(*it), P->intersection(vNeighbours), X->intersection(vNeighbours));
        delete vNeighbours;
        
        SubGraph *newP = P->remove(*it);
        SubGraph * newX = X->add(*it);       
        delete P;
        delete X;
        P = newP;
        X = newX;
    }
    
    delete P;
    delete X;
    delete R;
}
