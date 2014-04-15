/*
 * lsSolver.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */
 
#include "lsSolver.hpp"

LSState::LSState(const LSState & s) :
        graph(s.graph),
        verticesColors(s.verticesColors),
        nVertices(s.nVertices),
        nColors(s.nColors)
{
}

LSState::LSState(Graph *g, const Solution &s) :
        graph(g),
        verticesColors(s.verticesColors),
        nVertices(graph->nVertices),
        nColors(s.colors())
{
}

LSSolver::LSSolver(Graph *g, const Solution &s) :
        graph(g),
        state(g,s)
{
}

Solution LSSolver::solution() {
    Solution s(graph->nVertices);
    s.verticesColors.assign(state.verticesColors.begin(), state.verticesColors.end());
    return s;
}
