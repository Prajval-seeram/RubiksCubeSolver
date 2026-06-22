#ifndef IDASTAR_H
#define IDASTAR_H

#include "Node.h"
#include "Heuristic.h"
#include "SearchStats.h"

using namespace std;

class IDAStar
{
private:
    Heuristic heuristic;

    SearchStats stats;

    bool search(Node node,
                int threshold,
                vector<Move>& solution);

public:
    vector<Move> solve(Node root);

    SearchStats getStats() const;
};

#endif