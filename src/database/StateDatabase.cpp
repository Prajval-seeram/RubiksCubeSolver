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
};

StateKey StateDatabase::getKey(const Cube& cube) const
{
    return hash<string>{}(cube.encodeState());
}

size_t StateDatabase::size() const
{
    return lookup.size();
}

bool StateDatabase::contains(const Cube& cube) const
{
    return lookup.find(getKey(cube))
        != lookup.end();
}

vector<Move> StateDatabase::getSolution(
    const Cube& cube
) const
{
    vector<Move> solution;

    auto it =
        lookup.find(getKey(cube));

    if(it == lookup.end())
    {
        return solution;
    }

    uint32_t index =
        it->second;

    while(index != 0)
    {
        const DBEntry& entry =
            entries[index];

        solution.push_back(
            entry.moveToParent
        );

        index =
            entry.parentIndex;
    }

    return solution;
}

void StateDatabase::build(int maxDepth)
{
    lookup.clear();
    entries.clear();
    keys.clear();

    Cube solved;

    StateKey rootKey =
        getKey(solved);

    lookup[rootKey] = 0;

    entries.push_back(
    {
        0,
        Move::U
    });

    keys.push_back(rootKey);

    queue<BFSNode> q;

    q.push(
    {
        solved,
        0
    });

    MoveGenerator generator;

    while(!q.empty())
    {
        BFSNode current =
            q.front();

        q.pop();

        if(current.depth >= maxDepth)
        {
            continue;
        }

        Node currentNode;

        currentNode.cube =
            current.cube;

        currentNode.depth =
            current.depth;

        vector<Node> children =
            generator.generateChildren(
                currentNode
            );

        uint32_t currentIndex =
            lookup[
                getKey(current.cube)
            ];

        for(auto& child : children)
        {
            StateKey key =
                getKey(child.cube);

            if(
                lookup.find(key)
                != lookup.end()
            )
            {
                continue;
            }

            uint32_t childIndex =
                static_cast<uint32_t>(
                    entries.size()
                );

            lookup[key] =
                childIndex;

            entries.push_back(
            {
                currentIndex,
                inverseMove(
                    child.lastMove
                )
            });

            keys.push_back(key);

            q.push(
            {
                child.cube,
                current.depth + 1
            });
        }
    }

    cout
        << "States Stored: "
        << lookup.size()
        << "\n";
}

bool StateDatabase::save(
    const string& filename
) const
{
    ofstream out(
        filename,
        ios::binary
    );

    if(!out)
    {
        return false;
    }

    uint64_t entryCount =
        entries.size();

    uint64_t keyCount =
        keys.size();

    out.write(
        reinterpret_cast<const char*>(
            &entryCount
        ),
        sizeof(entryCount)
    );

    out.write(
        reinterpret_cast<const char*>(
            entries.data()
        ),
        entryCount *
        sizeof(DBEntry)
    );

    out.write(
        reinterpret_cast<const char*>(
            &keyCount
        ),
        sizeof(keyCount)
    );

    out.write(
        reinterpret_cast<const char*>(
            keys.data()
        ),
        keyCount *
        sizeof(StateKey)
    );

    return out.good();
}

bool StateDatabase::load(
    const string& filename
)
{
    ifstream in(
        filename,
        ios::binary
    );

    if(!in)
    {
        return false;
    }

    lookup.clear();
    entries.clear();
    keys.clear();

    uint64_t entryCount;

    if(!in.read(
        reinterpret_cast<char*>(
            &entryCount
        ),
        sizeof(entryCount)
    ))
    {
        return false;
    }

    entries.resize(entryCount);

    if(!in.read(
        reinterpret_cast<char*>(
            entries.data()
        ),
        entryCount *
        sizeof(DBEntry)
    ))
    {
        return false;
    }

    uint64_t keyCount;

    if(!in.read(
        reinterpret_cast<char*>(
            &keyCount
        ),
        sizeof(keyCount)
    ))
    {
        return false;
    }

    keys.resize(keyCount);

    if(!in.read(
        reinterpret_cast<char*>(
            keys.data()
        ),
        keyCount *
        sizeof(StateKey)
    ))
    {
        return false;
    }

    for(uint32_t i = 0;
        i < keys.size();
        i++)
    {
        lookup[keys[i]] = i;
    }

    return true;
}