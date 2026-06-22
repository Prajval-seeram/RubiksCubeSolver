#include <iostream>
#include <chrono>

#include "search/IDAStar.h"
#include "search/Node.h"
#include "search/SearchStats.h"
#include "cube/Moves.h"

using namespace std;

int main()
{
    Node root;

    root.cube.applyMove(Move::R);
    root.cube.applyMove(Move::U);
    root.cube.applyMove(Move::F);
    root.cube.applyMove(Move::L);
    root.cube.applyMove(Move::R);
    root.cube.applyMove(Move::U);
    root.cube.applyMove(Move::F);
    root.cube.applyMove(Move::L);

    IDAStar ida;

    auto start =
        chrono::high_resolution_clock::now();

    vector<Move> solution =
        ida.solve(root);

    auto end =
        chrono::high_resolution_clock::now();

    SearchStats stats =
        ida.getStats();

    cout << "Solution Length: "
         << solution.size()
         << "\n\n";

    cout << "Solution:\n";

    for(Move move : solution)
    {
        cout << moveToString(move)
             << " ";
    }

    cout << "\n\n";

    cout << "Nodes Expanded: "
         << stats.nodesExpanded
         << "\n";

    cout << "Solve Time: "
         << chrono::duration_cast<
                chrono::milliseconds
            >(end - start).count()
         << " ms\n";

    return 0;
}