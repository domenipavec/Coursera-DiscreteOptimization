/*
 * solver-greedy.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "solver.hpp"

#include <utility>
#include <algorithm>
#include <limits>
#include <iostream>
#include <chrono>
using namespace std::chrono;
static const double EPSILON = 0.00001;

typedef std::pair<uint32_t, uint32_t> Edge;
typedef std::pair<Edge, double> EdgeCost;
typedef std::vector<EdgeCost> EdgeCostList;

static bool compareEdgeCost (EdgeCost i1, EdgeCost i2) {
    return i1.second < i2.second;
}

Solution opt2Solve(const Data & data, const Solution & solution) {
    solution.visualize();
    
    Solution s(solution);
    
    while (1) {
        // sort edges, calculate total cost
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        EdgeCostList ecl;
        double totalCost = 0;
        ecl.reserve(data.nPoints);
        uint32_t previousPoint = s.order.back();
        for (std::vector<uint32_t>::iterator it = s.order.begin(); it != s.order.end(); ++it) {
            double cost = data.getDistance(previousPoint, *it);
            ecl.push_back(EdgeCost(Edge(previousPoint, *it), cost));
            totalCost += cost;
            previousPoint = *it;
        }
        std::sort(ecl.begin(), ecl.end(), compareEdgeCost);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

        std::cerr << "It took me " << time_span.count() << " seconds.";
        std::cerr << std::endl;
        
        // replace most expensive edge with best solution (2opt)
        double bestCost = std::numeric_limits<double>::max();
        uint32_t bestId = 0;
        EdgeCost toReplace;
        for (uint32_t j = data.nPoints - 1; j > 0; j--) {
            for (uint32_t i = 0; i < j; i++) {
                double cost = totalCost - ecl[j].second;
                cost -= ecl[i].second;
                // must connect firsts and seconds to maintain connectivity
                cost += data.getDistance(ecl[j].first.first, ecl[i].first.first);
                cost += data.getDistance(ecl[j].first.second, ecl[i].first.second);
                if (cost < bestCost) {
                    bestCost = cost;
                    bestId = i;
                    toReplace = ecl[j];
                }
            }
            if (bestCost + EPSILON < totalCost) {
                break;
            }
        }
        
        // break if cost larger
        if (bestCost > totalCost - EPSILON) {
            break;
        }
        
        // construct solution
        std::vector<uint32_t>::iterator reverse[2];
        uint8_t reverseId = 0;
//         std::cerr << toReplace.first.first << ' ';
//         std::cerr << toReplace.first.second << ' ';
//         std::cerr << ecl[bestId].first.first << ' ';
//         std::cerr << ecl[bestId].first.second << std::endl;
//         std::cerr << bestCost << ' ' << totalCost << std::endl;
        for (std::vector<uint32_t>::iterator it = s.order.begin(); it != s.order.end(); ++it) {
            if (reverseId == 0) {
                if (*it == toReplace.first.second || *it == ecl[bestId].first.second) {
                    reverseId = 1;
                    reverse[0] = it;
                }
            } else {
                if (*it == toReplace.first.first || *it == ecl[bestId].first.first) {
                    reverse[1] = ++it;
                    break;
                }
            }
        }
        std::reverse(reverse[0], reverse[1]);
        s.visualize();
    }
    
    return s;
}

