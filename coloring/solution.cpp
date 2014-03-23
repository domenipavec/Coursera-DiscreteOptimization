/*
 * solution.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "solution.hpp"

Solution::Solution(uint16_t n) {
    optimal = false;
    nVertices = n;
    verticesColors = new uint16_t[nVertices];
}

uint16_t Solution::colors() const {
    uint16_t max = 0;
    for (uint16_t i = 0; i < nVertices; i++) {
        if (verticesColors[i] > max) {
            max = verticesColors[i];
        }
    }
    return max+1;
}

std::ostream &operator<<(std::ostream &os, Solution const &s) { 
     os << s.colors() << " " << s.optimal << std::endl;
     for (uint16_t i = 0; i < s.nVertices; i++) {
         os << s.verticesColors[i] << " ";
     }
     return os;
}
