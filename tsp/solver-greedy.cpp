/*
 * solver-greedy.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "solver.hpp"

#include <unordered_set>

Solution solve(const Data & data, const Solution & solution) {
    Solution s(solution);
    
    std::unordered_set<uint32_t> notUsed(s.order.begin(), s.order.end());
    notUsed.erase(0);
    
    for (uint32_t i = 1; i < data.nPoints; i++) {
        std::vector<uint32_t>::const_iterator it = data.orderedNeighbours[s.order[i-1]].cbegin();
        while (notUsed.find(*it) == notUsed.cend()) ++it;
        s.order[i] = *it;
        notUsed.erase(*it);
    }
    
    return s;
}

