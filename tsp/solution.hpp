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
#include <vector>
#include <ostream>

#include "data.hpp"

#define VISUALIZE_ENABLE 0

class Solution {
    public:
        Solution(const Data & d);
        void visualize() const;
        double getTotal() const;

    public:
        const Data & data;
        std::vector<uint32_t> order;
        bool optimal;
};

std::ostream &operator<<(std::ostream &os, Solution const &s);

#endif
