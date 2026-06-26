#include "StateDatabase.h"

#include "../search/MoveGenerator.h"
#include "../search/Node.h"

#include <queue>
#include <iostream>
#include <functional>
#include <fstream>

using namespace std;

struct BFSNode
{
    Cube cube;
    int depth;
    Move lastMove;
};

StateKey StateDatabase::getKey(const Cube& cube) const
{
    uint64_t h = 14695981039346656037ULL;
    const uint64_t p = 1099511628211ULL;

    const char* fcs[6] = { 
        cube.getUFacePtr(), cube.getDFacePtr(), cube.getFFacePtr(), 
        cube.getBFacePtr(), cube.getLFacePtr(), cube.getRFacePtr() 
    };

    for (int f = 0; f < 6; ++f) 
    {
        for (int i = 0; i < 9; ++i) 
        {
            h ^= static_cast<uint64_t>(fcs[f][i]);
            h *= p;
        }
    }
    
    return h;
}

size_t StateDatabase::size() const
{
    return lookup.size();
}

bool StateDatabase::contains(const Cube& cube) const
{
    return lookup.find(getKey(cube)) != lookup.end();
}

vector<Move> StateDatabase::getSolution(const Cube& cube) const
{
    vector<Move> sol;
    auto it = lookup.find(getKey(cube));

    if(it == lookup.end())
    {
        return sol;
    }

    uint32_t idx = it->second;

    while(idx != 0)
    {
        const DBEntry& e = entries[idx];
        sol.push_back(e.moveToParent);
        idx = e.parentIndex;
    }

    return sol;
}

void StateDatabase::build(int maxDepth)
{
    lookup.clear();
    entries.clear();
    keys.clear();

    lookup.reserve(110000000);
    entries.reserve(110000000);
    keys.reserve(110000000);

    Cube solved;
    StateKey rKey = getKey(solved);
    lookup[rKey] = 0;
    entries.push_back({0, Move::U});
    keys.push_back(rKey);

    queue<BFSNode> q;
    q.push({solved, 0, Move::U});

    MoveGenerator gen;

    while(!q.empty())
    {
        BFSNode curr = q.front();
        q.pop();

        if(curr.depth >= maxDepth)
        {
            continue;
        }

        uint32_t currIdx = lookup[getKey(curr.cube)];

        Node n;
        n.cube = curr.cube;
        n.depth = curr.depth;
        n.lastMove = curr.lastMove;

        vector<Node> ch = gen.generateChildren(n);

        for(const Node& c : ch)
        {
            StateKey k = getKey(c.cube);

            if(lookup.find(k) != lookup.end())
            {
                continue;
            }

            uint32_t chIdx = static_cast<uint32_t>(entries.size());
            lookup[k] = chIdx;
            entries.push_back({currIdx, inverseMove(c.lastMove)});
            keys.push_back(k);

            q.push({c.cube, c.depth, c.lastMove});
        }
    }

    cout << "States Stored: " << lookup.size() << "\n";
}

bool StateDatabase::save(const string& filename) const
{
    ofstream out(filename, ios::binary);

    if(!out)
    {
        return false;
    }

    uint64_t eCount = entries.size();
    uint64_t kCount = keys.size();

    out.write(reinterpret_cast<const char*>(&eCount), sizeof(eCount));
    out.write(reinterpret_cast<const char*>(entries.data()), eCount * sizeof(DBEntry));
    out.write(reinterpret_cast<const char*>(&kCount), sizeof(kCount));
    out.write(reinterpret_cast<const char*>(keys.data()), kCount * sizeof(StateKey));

    return out.good();
}

bool StateDatabase::load(const string& filename)
{
    ifstream in(filename, ios::binary);

    if(!in)
    {
        return false;
    }

    lookup.clear();
    entries.clear();
    keys.clear();

    uint64_t eCount;

    if(!in.read(reinterpret_cast<char*>(&eCount), sizeof(eCount)))
    {
        return false;
    }

    entries.resize(eCount);

    if(!in.read(reinterpret_cast<char*>(entries.data()), eCount * sizeof(DBEntry)))
    {
        return false;
    }

    uint64_t kCount;

    if(!in.read(reinterpret_cast<char*>(&kCount), sizeof(kCount)))
    {
        return false;
    }

    keys.resize(kCount);

    if(!in.read(reinterpret_cast<char*>(keys.data()), kCount * sizeof(StateKey)))
    {
        return false;
    }

    for(uint32_t i = 0; i < keys.size(); i++)
    {
        lookup[keys[i]] = i;
    }

    return true;
}

int StateDatabase::getDistance(const Cube& cube) const
{
    auto it = lookup.find(getKey(cube));

    if(it == lookup.end())
    {
        return -1;
    }

    int dist = 0;
    uint32_t idx = it->second;

    while(idx != 0)
    {
        dist++;
        idx = entries[idx].parentIndex;
    }

    return dist;
}