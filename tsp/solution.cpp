/*
 * solution.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "solution.hpp"

#include <stdlib.h>
#include <iostream>

Solution::Solution(const Data & d)
    : data(d), order(data.nPoints, 0), optimal(false)
{
    for (uint32_t i = 0; i < data.nPoints; i++) {
        order[i] = i;
    }
}
    
void Solution::visualize() const {
    if (VISUALIZE_ENABLE) {
        if (!system(NULL)) {
            std::cerr << "Cannot process system command!" << std::endl;
            exit(-1);
        }
        
        std::string command("./visualize.py ");
        command += data.filename;
        
        for (std::vector<uint32_t>::const_iterator it = order.cbegin(); it != order.cend(); ++it) {
            command += " ";
            command += std::to_string(*it);
        }
        
        int __attribute__((unused)) system_return = system(command.c_str());
    }
}

double Solution::getTotal() const {
    double total = 0;
    uint32_t previous = order.back();
    for (std::vector<uint32_t>::const_iterator it = order.cbegin(); it != order.cend(); ++it) {
        total += data.getDistance(previous, *it);
        previous = *it;
    }
    return total;
}

std::ostream &operator<<(std::ostream &os, Solution const &s) {
    os << s.getTotal() << ' ' << s.optimal << std::endl;
    for (std::vector<uint32_t>::const_iterator it = s.order.cbegin(); it != s.order.cend(); ++it) {
        os << *it << ' ';
    }
    os << std::endl;
    return os;
}