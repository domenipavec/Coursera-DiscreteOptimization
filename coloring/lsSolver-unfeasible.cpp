/*
 * lsSolver-unfeasible.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */
 
#include "lsSolver.hpp"

#include <algorithm>
#include <iostream>
#include <stdlib.h>

typedef std::pair<uint16_t, uint16_t> colorPair;
typedef std::vector<colorPair> pairList;

bool sortFunctionDesc(colorPair p1, colorPair p2) {
    return p1.second > p2.second;
}
bool sortFunctionAsc(colorPair p1, colorPair p2) {
    return (p1.second < p2.second || (p1.second == p2.second && (rand() %2 == 0)));
}
bool sortFunctionAscRand(colorPair p1, colorPair p2) {
    return (p1.second < p2.second ||(rand() %2 == 0));
}

uint16_t getLowestUsedColor(const LSState & state) {
    // init color count
    pairList colorCount(state.nColors, colorPair(0,0));
    for (uint16_t i = 0; i < state.nColors; i++) {
        colorCount[i].first = i;
    }
    
    // count colors
    for (intList::const_iterator it = state.verticesColors.cbegin(); it != state.verticesColors.cend(); ++it) {
        colorCount[*it].second++;
    }
    
    return std::min_element(colorCount.begin(), colorCount.end(), sortFunctionAsc)->first;
}

void removeColor(LSState & state, uint16_t color) {
    // one color less
    state.nColors--;
    
    // change all color numbers after this one (inclusive)
    for (uint16_t i = 0; i < state.nVertices; i++) {
        if (state.verticesColors[i] == color) {
            state.verticesColors[i] = rand() % state.nColors;
            state.infeasible.insert(i);
        } else if (state.verticesColors[i] > color) {
            state.verticesColors[i]--;
        }
    }
}

uint16_t getCollisionsVertex(const LSState & state, uint16_t vertex) {
    uint16_t c = 0;
    for (intList::const_iterator it = state.graph->neighbours[vertex].cbegin();
            it != state.graph->neighbours[vertex].cend(); ++it) {
        if (state.verticesColors[vertex] == state.verticesColors[*it]) {
            c++;
        }
    }
    return c;
}

uint16_t getCollisions(const LSState & state) {
    uint16_t c = 0;
    for (intSet::const_iterator it = state.infeasible.cbegin(); it != state.infeasible.cend(); ++it) {
        c += getCollisionsVertex(state, *it);
    }
    return c;
}

uint16_t getBestColor(LSState & state, uint16_t vertex, uint16_t & bestColor) {
    // init color count
    pairList colorCount(state.nColors, colorPair(0,0));
    for (uint16_t i = 0; i < state.nColors; i++) {
        colorCount[i].first = i;
    }
    
    // count neighbours per color
    for (intList::const_iterator it = state.graph->neighbours[vertex].cbegin();
            it != state.graph->neighbours[vertex].cend(); ++it) {
        colorCount[state.verticesColors[*it]].second++;
    }
    
    // select best
    uint16_t currentColls = colorCount[state.verticesColors[vertex]].second;
    pairList::iterator min = std::min_element(colorCount.begin(), colorCount.end(), sortFunctionAsc);
    uint16_t bestColls = min->second;
    bestColor = min->first;
    return currentColls - bestColls;
}

void LSSolver::solve() {
    LSState oldState = state;
    const uint16_t timesMAX = 200;
    uint16_t times = 0;
    while (state.nColors > 100) {
        uint16_t color = getLowestUsedColor(state);
        
        removeColor(state, color);
        times = 0;
        std::cerr << "Inf: " << state.infeasible.size() << " Colls: " << getCollisions(state) << std::endl;
        
        std::cerr << "Color " << color << " removed. nColors: " << state.nColors << std::endl;
        while (state.infeasible.size() > 0) {
            uint16_t bestVertex = 0xffff;
            uint16_t bestColor = 0xffff;
            uint16_t bestImprovement = 0;
            
            // iterate over infeasible list
            for (intSet::iterator it = state.infeasible.begin(); it != state.infeasible.end(); ++it) {
                // change this vertex
                uint16_t color;
                uint16_t improvement = getBestColor(state, *it, color);
                if (improvement > bestImprovement || (improvement == bestImprovement && (rand() % 2 == 0))) {
                    bestColor = color;
                    bestImprovement = improvement;
                    bestVertex = *it;
                }
                
                // change all neighbours
                for (intList::iterator neighbour = state.graph->neighbours[*it].begin(); neighbour != state.graph->neighbours[*it].end(); ++neighbour) {
                    if (state.verticesColors[*it] == state.verticesColors[*neighbour] || rand() %200 == 0) {
                        improvement = getBestColor(state, *neighbour, color);
                        if (improvement > bestImprovement || (improvement == bestImprovement && (rand() % 2 == 0))) {
                            bestColor = color;
                            bestImprovement = improvement;
                            bestVertex = *neighbour;
                        }
                    }
                }
            }
           
            // change chosen vertex or terminate
            if (bestVertex != 0xffff) {
                state.verticesColors[bestVertex] = bestColor;
                if (getCollisionsVertex(state, bestVertex) != 0) {
                    state.infeasible.insert(bestVertex);
                } else {
                    state.infeasible.erase(bestVertex);
                }
            } else {
                if (times < timesMAX) {
                    times++;
                    if (times % 50 == 0) {
                        std::cerr << "Times: " << times << std::endl;
                    }
                    continue;
                } else {
                     std::cerr << "Reset" << std::endl;
                     break;
                }
            }
     
        }
        if (times == timesMAX) {
            state = oldState;
            times = 0;
        }
    }
}
