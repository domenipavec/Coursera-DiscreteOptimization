/*
 * data.cpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#include "data.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

PointsSort::PointsSort(const Data & d, const uint32_t c) 
    : data(d), current(c) {
}

bool PointsSort::operator() (uint32_t i, uint32_t j) {
    return data.getDistance(current, i) < data.getDistance(current, j);
}

Data::Data(const char * const fn)
    :filename(fn)
{
    // points from file
    ifstream ifile;
    ifile.open(fn, ios::in);
    if (ifile.is_open()) {
        ifile >> nPoints;
        cerr << "Points: " << nPoints << endl;
        for (uint32_t i = 0; i < nPoints; i++) {
            Point p;
            ifile >> p.x;
            ifile >> p.y;
            points.push_back(p);
        }
    } else {
        cerr << "Could not open file " << fn << endl;
    }

    // calculate distances
    dist.assign(nPoints, std::vector<double>());
    #pragma omp parallel for
    for (uint32_t i = 1; i < nPoints; i++) {
        dist[i].reserve(i);
        for (uint32_t j = 0; j < i; j++) {
            dist[i].push_back(hypot(points[i].x - points[j].x, points[i].y - points[j].y));
        }
    }

    // fill and order neighbours
    orderedNeighbours.assign(nPoints, std::vector<uint32_t>(nPoints - 1, 0));
    #pragma omp parallel for
    for (uint32_t i = 0; i < nPoints; i++) {
        uint32_t j = 0;
        for (std::vector<uint32_t>::iterator it = orderedNeighbours[i].begin(); it != orderedNeighbours[i].end(); ++it) {
            if (i == j) {
                j++;
            }
            *it = j;
            j++;
        }
        std::sort(orderedNeighbours[i].begin(), orderedNeighbours[i].end(), PointsSort(*this, i));
    }
}

double Data::getDistance(const uint32_t i1, const uint32_t i2) const {
    if (i1 == i2) {
        return 0;
    } else if (i1 < i2) {
        return dist[i2][i1];
    } else {
        return dist[i1][i2];
    }
}