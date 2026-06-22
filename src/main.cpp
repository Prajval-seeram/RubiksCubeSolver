#include <iostream>

#include "search/IDDFS.h"
#include "search/Node.h"
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



    IDDFS iddfs;

    vector<Move> solution =
        iddfs.solve(root, 10);

    cout << "Solution:\n";

    for(Move move : solution)
    {
        cout << moveToString(move)
             << " ";
    }

    cout << endl;

    return 0;
}