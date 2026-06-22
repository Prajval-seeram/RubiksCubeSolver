#include "Solver.h"

#include "../search/IDAStar.h"
#include "../search/Node.h"

#include <chrono>

using namespace std;

SolveResult Solver::solve(const Cube& cube)
{
    SolveResult result;

    Node root;

    root.cube = cube;

    IDAStar ida;

    auto start =
        chrono::high_resolution_clock::now();

    vector<Move> solution =
        ida.solve(root);

    auto end =
        chrono::high_resolution_clock::now();

    SearchStats stats =
        ida.getStats();

    result.solution = solution;

    result.nodesExpanded =
        stats.nodesExpanded;

    result.solveTimeMs =
        chrono::duration_cast<
            chrono::milliseconds
        >(end - start).count();

    result.solved = true;

    return result;
}