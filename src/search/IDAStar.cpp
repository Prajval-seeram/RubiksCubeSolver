#include "IDAStar.h"
#include "MoveGenerator.h"
#include <algorithm>

using namespace std;

IDAStar::IDAStar(StateDatabase* d) {
    database = d;
}

bool IDAStar::search(Node n, int t, vector<Move>& s) {
    stats.nodesExpanded++;

    if (n.depth > 20) return false;

    int h = heuristic.misplacedStickers(n.cube) / 4;
    
    if (database) {
        int d = database->getDistance(n.cube);
        if (d != -1) h = d;
        else if (h < 7) h = 7;
    }

    int c = n.depth + h;

    if (c > t) return false;

    if (n.cube.isSolved()) {
        s = n.path;
        return true;
    }

    if (database && database->contains(n.cube)) {
        s = n.path;
        vector<Move> l = database->getSolution(n.cube);
        s.insert(s.end(), l.begin(), l.end());
        return true;
    }

    MoveGenerator m;
    vector<Node> k = m.generateChildren(n);

    struct O {
        int s;
        size_t i;
    };

    vector<O> v;
    v.reserve(k.size());
    for (size_t i = 0; i < k.size(); ++i) {
        v.push_back({heuristic.misplacedStickers(k[i].cube) / 4, i});
    }

    sort(v.begin(), v.end(), [](const O& a, const O& b) {
        return a.s < b.s;
    });

    for (const auto& e : v) {
        if (search(k[e.i], t, s)) return true;
    }

    return false;
}

vector<Move> IDAStar::solve(Node r) {
    stats.nodesExpanded = 0;

    int t = heuristic.misplacedStickers(r.cube) / 4;
    
    if (database) {
        int d = database->getDistance(r.cube);
        if (d != -1) t = d;
        else if (t < 7) t = 7;
    }

    vector<Move> s;

    while (true) {
        s.clear();
        if (search(r, t, s)) return s;
        t++;
    }
}

SearchStats IDAStar::getStats() const {
    return stats;
}