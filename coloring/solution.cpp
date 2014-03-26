/*
 * solution.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "solution.hpp"
#include <algorithm>

Solution::Solution(uint16_t n)
        : optimal(false), nVertices(n) {
}

uint16_t Solution::colors() const {
    return (*std::max_element(verticesColors.begin(), verticesColors.end()))+1;
}

std::ostream &operator<<(std::ostream &os, Solution const &s) { 
     os << s.colors() << " " << s.optimal << std::endl;
     for (std::vector<uint16_t>::const_iterator it = s.verticesColors.cbegin(); it != s.verticesColors.cend(); ++it) {
         os << *it << " ";
     }
     return os;
}
