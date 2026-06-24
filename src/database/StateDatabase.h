#ifndef STATE_DATABASE_H
#define STATE_DATABASE_H

#include "../cube/Cube.h"
#include "../cube/Moves.h"

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <string>

using StateKey = uint64_t;

struct DBEntry
{
    uint32_t parentIndex;

    Move moveToParent;
};

class StateDatabase
{
public:

    void build(int maxDepth);

    bool contains(const Cube& cube) const;

    std::vector<Move> getSolution(
        const Cube& cube
    ) const;

    size_t size() const;

    bool save(const string& filename) const;
    bool load(const string& filename);

private:

    StateKey getKey(
        const Cube& cube
    ) const;

    std::unordered_map<
        StateKey,
        uint32_t
    > lookup;

    std::vector<DBEntry> entries;

    std::vector<StateKey> keys;
};

#endif