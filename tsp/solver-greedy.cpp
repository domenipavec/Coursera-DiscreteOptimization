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
#include <stdlib.h>

static const uint32_t iterations = 100;

Solution greedySolve(const Data & data, const Solution & solution) {
    Solution * best;
    double bestValue = 0;
    std::unordered_set<uint32_t> beginings;
    if (data.nPoints <= iterations) {
        beginings.insert(solution.order.begin(), solution.order.end());
    } else {
        while (beginings.size() < iterations) {
            beginings.insert(solution.order[rand() % solution.order.size()]);
        }
    }
    for (std::unordered_set<uint32_t>::iterator begin = beginings.begin(); begin != beginings.end(); begin++) {
        Solution *s = new Solution(solution);
        
        std::unordered_set<uint32_t> notUsed(s->order.begin(), s->order.end());
        notUsed.erase(*begin);
        s->order[0] = *begin;
        
        for (uint32_t i = 1; i < data.nPoints; i++) {
            std::vector<uint32_t>::const_iterator it = data.orderedNeighbours[s->order[i-1]].cbegin();
            while (notUsed.find(*it) == notUsed.cend()) ++it;
            s->order[i] = *it;
            notUsed.erase(*it);
        }
        
        double currValue = s->getTotal();
        if (bestValue == 0 || currValue < bestValue) {
            bestValue = currValue;
            best = s;
        } else {
            delete s;
        }
    }
    Solution t(*best);
    delete best;
    return t;
}

