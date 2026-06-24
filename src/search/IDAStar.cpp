#include "IDAStar.h"
#include "MoveGenerator.h"

using namespace std;

IDAStar::IDAStar(
    StateDatabase* db
)
{
    database = db;
}

bool IDAStar::search(
    Node node,
    int threshold,
    vector<Move>& solution)
{
    stats.nodesExpanded++;

    if(node.depth > 20)
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

if(database &&
   database->contains(node.cube))
{
    solution = node.path;

    vector<Move> tail =
        database->getSolution(
            node.cube
        );

    solution.insert(
        solution.end(),
        tail.begin(),
        tail.end()
    );

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
    stats.nodesExpanded = 0;

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

SearchStats IDAStar::getStats() const
{
    return stats;
}