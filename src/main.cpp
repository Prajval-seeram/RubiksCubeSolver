#include <iostream>
#include <chrono>

#include "database/StateDatabase.h"

using namespace std;

int main()
{
    StateDatabase db;

    auto start =
        chrono::high_resolution_clock::now();

    if(db.load("database.bin"))
    {
        cout
            << "Database loaded!\n";
    }
    else
    {
        cout
            << "Building database...\n";

        db.build(6);

        db.save("database.bin");

        cout
            << "Database saved!\n";
    }

    auto end =
        chrono::high_resolution_clock::now();

    cout
        << "States: "
        << db.size()
        << "\n";

    cout
        << "Time: "
        << chrono::duration_cast<
            chrono::milliseconds
        >(end - start).count()
        << " ms\n";

    return 0;
}