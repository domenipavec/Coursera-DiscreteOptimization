/*
 * solution.hpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <stdint.h>
#include <ostream>

class Solution {
    public:
        Solution(uint16_t n);
        uint16_t colors() const;
    public:
        bool optimal;
        uint16_t nVertices;
        uint16_t * verticesColors;    
};

std::ostream &operator<<(std::ostream &os, Solution const &s);

#endif
