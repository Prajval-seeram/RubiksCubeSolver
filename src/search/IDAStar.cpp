#include "IDAStar.h"
#include "MoveGenerator.h"

using namespace std;

bool IDAStar::search(
    Node node,
    int threshold,
    vector<Move>& solution)
{if(node.depth > 20)
{
    return false;
}
    int cost =
    node.depth +
    heuristic.misplacedStickers(node.cube) / 8;
    
    if(cost > threshold)
    {
        return false;
    }

    if(node.cube.isSolved())
    {
        solution = node.path;
        return true;
    }

    MoveGenerator generator;

    vector<Node> children =
        generator.generateChildren(node);

    for(Node child : children)
    {
        if(search(child,
                  threshold,
                  solution))
        {
            return true;
        }
    }

    return false;
}

vector<Move> IDAStar::solve(Node root)
{
    int threshold =
    heuristic.misplacedStickers(root.cube) / 8;

    vector<Move> solution;

    while(true)
    {
        solution.clear();

        if(search(root,
                  threshold,
                  solution))
        {
            return solution;
        }

        threshold++;
    }
}