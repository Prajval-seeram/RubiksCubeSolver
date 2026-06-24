#include <iostream>

#include "solver/Solver.h"
#include "search/Heuristic.h"

using namespace std;

int main()
{
    Solver solver;

    Cube cube;

    // 10-move benchmark
    cube.applyMove(Move::R);
    cube.applyMove(Move::U);
    cube.applyMove(Move::F);
    cube.applyMove(Move::L);
    cube.applyMove(Move::D);
    cube.applyMove(Move::B);
    cube.applyMove(Move::R);
    cube.applyMove(Move::U);
    cube.applyMove(Move::F);
    cube.applyMove(Move::L);
    cube.applyMove(Move::R);
    cube.applyMove(Move::U);
    cube.applyMove(Move::F);

    Heuristic h;

    cout
        << "Misplaced Stickers: "
        << h.misplacedStickers(cube)
        << "\n";

    cout
        << "Heuristic Value: "
        << h.misplacedStickers(cube) / 4
        << "\n\n";

    SolveResult result =
        solver.solve(cube);

    cout
        << "Solution Length: "
        << result.solution.size()
        << "\n";

    cout
        << "Nodes Expanded: "
        << result.nodesExpanded
        << "\n";

    cout
        << "Solve Time: "
        << result.solveTimeMs
        << " ms\n";

    return 0;
}