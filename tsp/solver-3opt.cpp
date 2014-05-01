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

static const double EPSILON = 0.00001;

typedef std::pair<uint32_t, uint32_t> Edge;
typedef std::pair<Edge, double> EdgeCost;
typedef std::vector<EdgeCost> EdgeCostList;

static bool compareEdgeCost (EdgeCost i1, EdgeCost i2) {
    return i1.second < i2.second;
}

void orderReverse(std::vector<uint32_t> & order, uint32_t i1, uint32_t i2) {
    std::vector<uint32_t>::iterator it1 = std::find(order.begin(), order.end(), i1);
    std::vector<uint32_t>::iterator it2 = std::find(order.begin(), order.end(), i2);
    if (it1 < it2) {
        std::reverse(it1, ++it2);
    } else {
        std::reverse(++it2, it1);
    }
}

Solution opt3Solve(const Data & data, const Solution & solution) {
    solution.visualize();
    
    Solution s(solution);
    
    while (1) {
        // sort edges, calculate total cost
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
        
        // do 3opt
        double bestCost = std::numeric_limits<double>::max();
        uint32_t bestId0 = 0;
        uint32_t bestId1 = 0;
        uint32_t bestId2 = 0;
        uint8_t bestCombo = 0;
        for (uint32_t i0 = data.nPoints - 1; i0 > 0; i0--) {
            double cost0 = totalCost - ecl[i0].second;
            for (uint32_t i1 = 1; i1 < i0; i1++) {
                double cost1 = cost0 - ecl[i1].second;
                for (uint32_t i2 = 0; i2 < i1; i2++) {
                    double cost2 = cost1 - ecl[i2].second;
                    for (uint8_t combo = 0; combo < 7; combo++) {
                        double cost = cost2;
                        switch (combo) {
                            case 0:
                                cost += data.getDistance(ecl[i0].first.first, ecl[i1].first.first);
                                cost += data.getDistance(ecl[i2].first.second, ecl[i0].first.second);
                                cost += data.getDistance(ecl[i1].first.second, ecl[i2].first.first);
                                break;
                            case 1:
                                cost += data.getDistance(ecl[i0].first.first, ecl[i1].first.first);
                                cost += data.getDistance(ecl[i2].first.second, ecl[i2].first.first);
                                cost += data.getDistance(ecl[i1].first.second, ecl[i0].first.second);
                                break;
                            case 2:
                                cost += data.getDistance(ecl[i0].first.first, ecl[i2].first.second);
                                cost += data.getDistance(ecl[i1].first.first, ecl[i2].first.first);
                                cost += data.getDistance(ecl[i1].first.second, ecl[i0].first.second);
                                break;
                            case 3:
                                cost += data.getDistance(ecl[i0].first.first, ecl[i2].first.second);
                                cost += data.getDistance(ecl[i1].first.first, ecl[i0].first.second);
                                cost += data.getDistance(ecl[i1].first.second, ecl[i2].first.first);
                                break;
                            case 4:
                                cost += data.getDistance(ecl[i0].first.first, ecl[i2].first.first);
                                cost += data.getDistance(ecl[i0].first.second, ecl[i1].first.first);
                                cost += data.getDistance(ecl[i1].first.second, ecl[i2].first.second);
                                break;
                            case 5:
                                cost += data.getDistance(ecl[i0].first.first, ecl[i2].first.first);
                                cost += data.getDistance(ecl[i0].first.second, ecl[i2].first.second);
                                cost += data.getDistance(ecl[i1].first.second, ecl[i1].first.first);
                                break;
                            case 6:
                                cost += data.getDistance(ecl[i0].first.first, ecl[i0].first.second);
                                cost += data.getDistance(ecl[i2].first.first, ecl[i1].first.first);
                                cost += data.getDistance(ecl[i1].first.second, ecl[i2].first.second);
                                break;
                        }
                        if (cost < bestCost) {
                            bestCost = cost;
                            bestId0 = i0;
                            bestId1 = i1;
                            bestId2 = i2;
                            bestCombo = combo;
                        }
                    }
                }
            }
//             if (bestCost + EPSILON < totalCost) {
//                 break;
//             }
        }
        
        // break if cost larger
        if (bestCost > totalCost - EPSILON) {
            break;
        }
        
        // construct solution
        switch (bestCombo) {
            case 0:
                orderReverse(s.order, ecl[bestId1].first.second, ecl[bestId0].first.first); // 1
                orderReverse(s.order, ecl[bestId0].first.second, ecl[bestId2].first.first); // 3
                break;
            case 1:
                orderReverse(s.order, ecl[bestId1].first.second, ecl[bestId0].first.first); // 1
                break;
            case 2:
                orderReverse(s.order, ecl[bestId1].first.second, ecl[bestId0].first.first); // 1
                orderReverse(s.order, ecl[bestId2].first.second, ecl[bestId1].first.first); // 2
                break;
            case 3:
                orderReverse(s.order, ecl[bestId1].first.second, ecl[bestId0].first.first); // 1
                orderReverse(s.order, ecl[bestId2].first.second, ecl[bestId1].first.first); // 2
                orderReverse(s.order, ecl[bestId0].first.second, ecl[bestId2].first.first); // 3
                break;
            case 4:
                orderReverse(s.order, ecl[bestId2].first.second, ecl[bestId1].first.first); // 2
                orderReverse(s.order, ecl[bestId0].first.second, ecl[bestId2].first.first); // 3
                break;
            case 5:
                orderReverse(s.order, ecl[bestId0].first.second, ecl[bestId2].first.first); // 3
                break;
            case 6:
                orderReverse(s.order, ecl[bestId2].first.second, ecl[bestId1].first.first); // 2
                break;
        }
        
        s.visualize();
    }
    
    return s;
}

