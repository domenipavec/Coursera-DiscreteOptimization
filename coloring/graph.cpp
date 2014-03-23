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

Graph::Graph(const char * const fn) {
    ifstream ifile;
    ifile.open(fn, ios::in);
    if (ifile.is_open()) {
        ifile >> nVertices;
        ifile >> nEdges;
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
