#ifndef SOLVER_H
#define SOLVER_H

#include "../cube/Cube.h"

#include "SolveResult.h"

class Solver
{
public:
    SolveResult solve(const Cube& cube);
};

#endif