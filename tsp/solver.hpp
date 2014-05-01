/*
 * solver.hpp
 * 
 * Copyright 2014 Domen <domen.ipavec@z-v.si>
 * 
 * See LICENSE.
 * 
 */

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "solution.hpp"
#include "data.hpp"

Solution greedySolve(const Data & data, const Solution & solution);
Solution opt2Solve(const Data & data, const Solution & solution);
Solution opt3Solve(const Data & data, const Solution & solution);
Solution optkSolve(const Data & data, const Solution & solution);

#endif
