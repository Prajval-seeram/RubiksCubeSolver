#include <iostream>

#include "solver/Solver.h"

using namespace std;

int main()
{
    Cube cube;

    cube.applyMove(Move::R);
    cube.applyMove(Move::U);
    cube.applyMove(Move::F);
    cube.applyMove(Move::L);

    Solver solver;

    SolveResult result =
        solver.solve(cube);

    cout << "Solved: "
         << result.solved
         << "\n";

    cout << "Solution Length: "
         << result.solution.size()
         << "\n";

    cout << "Nodes Expanded: "
         << result.nodesExpanded
         << "\n";

    cout << "Solve Time: "
         << result.solveTimeMs
         << " ms\n";

    return 0;
}