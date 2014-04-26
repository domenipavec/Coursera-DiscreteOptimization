/*
 * data.hpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#ifndef DATA_HPP
#define DATA_HPP

#include <stdint.h>
#include <vector>
#include <utility>

struct Point {
    double x;
    double y;
};

class Data {
    public:
        Data(const char * const fn);
        double getDistance(const uint32_t i1, const uint32_t i2) const;
        
    public:
        uint32_t nPoints;
        std::vector<Point> points;
        const char * filename;
        std::vector<std::vector<uint32_t> > orderedNeighbours;
        
    private:
        std::vector<std::vector<double> > dist;
};

class PointsSort {
    public:
        PointsSort(const Data & d, const uint32_t c);
        bool operator() (uint32_t i, uint32_t j);
        
    public:
        const Data & data;
        const uint32_t current;
};

#endif
